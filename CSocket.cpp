#include "CSocket.h"

/*
*/
CSocket::CSocket()
{
	memset(this, 0x00, sizeof(CSocket));
}

/*
*/
CSocket::CSocket(CErrorLog* errorLog)
{
	memset(this, 0x00, sizeof(CSocket));

	m_errorLog = errorLog;

	m_addrHints.ai_family = AF_INET;
	m_addrHints.ai_socktype = SOCK_STREAM;
	m_addrHints.ai_protocol = IPPROTO_TCP;
	m_addrHints.ai_flags = AI_PASSIVE;

	m_optval = 1;
}

/*
*/
CSocket::~CSocket()
{

}

/*
*/
SOCKET CSocket::Accept()
{
	m_assignedSocket = accept(m_socket, m_addrResult->ai_addr, (int32_t*)&m_addrResult->ai_addrlen);

	if (m_assignedSocket == SOCKET_ERROR)
	{
		switch (WSAGetLastError())
		{
		case WSAEINTR:
		case WSAENOTCONN:
		case WSAENOTSOCK:
		case WSAETIMEDOUT:
		{
			break;
		}
		default:
		{
			break;
		}
		}

		return 0;
	}
	else if (m_assignedSocket == INVALID_SOCKET)
	{
		m_errorLog->WriteWinsockErrorMessage(true, "CSocket::Accept::accept:INVALID_SOCKET:");

		m_state = CSocket::State::E_FAILED;

		return 0;
	}

	return m_assignedSocket;
}

/*
*/
bool CSocket::CreateConnectSocket(const char* address, const char* port)
{
	if (address)
	{
		strcpy_s(m_ip, CSocket::E_IP_LENGTH, address);
		strcpy_s(m_port, CSocket::E_PORT_LENGTH, port);
	}
	else
	{
		strcpy_s(m_ip, CSocket::E_IP_LENGTH, "127.0.0.1");
		strcpy_s(m_port, CSocket::E_PORT_LENGTH, "49152");
	}

	m_result = getaddrinfo(m_ip, m_port, &m_addrHints, &m_addrResult);

	if (m_result != 0)
	{
		m_errorLog->WriteError(true, "CSocket::CreateSocket::getaddrinfo:%i\n", m_result);

		m_state = CSocket::State::E_FAILED;

		return false;
	}

	for (m_addrPtr = m_addrResult; m_addrPtr != NULL; m_addrPtr = m_addrPtr->ai_next)
	{
		m_socket = socket(m_addrPtr->ai_family, m_addrPtr->ai_socktype, m_addrPtr->ai_protocol);

		if (m_socket == INVALID_SOCKET)
		{
			m_errorLog->WriteWinsockErrorMessage(true, "CSocket::CreateSocket::socket:");

			continue;
		}

		m_result = connect(m_socket, m_addrPtr->ai_addr, (int32_t)m_addrPtr->ai_addrlen);

		if (m_result == SOCKET_ERROR)
		{
			m_errorLog->WriteWinsockErrorMessage(true, "CSocket::ConnectSocket::connect:");

			closesocket(m_socket);

			m_state = CSocket::State::E_FAILED;

			return false;
		}

		break;
	}

	freeaddrinfo(m_addrResult);

	m_addrResult = 0;

	gethostname(m_hostname, CSocket::E_HOSTNAME_LENGTH);

	m_errorLog->WriteError(true, "CSocket::CreateSocket::hostname:%s\n", m_hostname);

	m_state = CSocket::State::E_CONNECTED;

	return true;
}

/*
*/
bool CSocket::CreateListenSocket(const char* port)
{
	if (port)
	{
		strcpy_s(m_port, CSocket::E_PORT_LENGTH, port);
	}
	else
	{
		strcpy_s(m_port, CSocket::E_PORT_LENGTH, "49152");
	}

	m_result = getaddrinfo(NULL, m_port, &m_addrHints, &m_addrResult);

	if (m_result != 0)
	{
		m_errorLog->WriteError(true, "CSocket::CreateListenSocket::getaddrinfo:%i\n", m_result);

		m_state = CSocket::State::E_FAILED;

		return false;
	}

	m_socket = socket(m_addrResult->ai_family, m_addrResult->ai_socktype, m_addrResult->ai_protocol);

	if (m_socket == INVALID_SOCKET)
	{
		m_errorLog->WriteWinsockErrorMessage(true, "CSocket::CreateListenSocket::socket:");

		freeaddrinfo(m_addrResult);

		m_state = CSocket::State::E_FAILED;

		return false;
	}

	m_result = setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&m_optval, sizeof(int32_t));

	if (m_result == SOCKET_ERROR)
	{
		m_errorLog->WriteWinsockErrorMessage(true, "CSocket::CreateListenSocket::setsockopt:");

		m_state = CSocket::State::E_FAILED;

		return false;
	}

	m_result = bind(m_socket, m_addrResult->ai_addr, (int32_t)m_addrResult->ai_addrlen);

	if (m_result == SOCKET_ERROR)
	{
		m_errorLog->WriteWinsockErrorMessage(true, "CSocket::CreateListenSocket::bind:");

		m_state = CSocket::State::E_FAILED;

		return false;
	}

	m_state = CSocket::State::E_CONNECTED;

	return true;
}

/*
*/
bool CSocket::Listen()
{
	m_result = listen(m_socket, SOMAXCONN);

	if (m_result == SOCKET_ERROR)
	{
		m_errorLog->WriteWinsockErrorMessage(true, "CSocket::StartListenSocket::listen:");

		m_state = CSocket::State::E_FAILED;

		return false;
	}

	return true;
}

/*
*/
int32_t CSocket::Receive(char* data, int32_t length)
{
	m_totalBytes = recv(m_socket, data, length, 0);

	if (m_totalBytes == INVALID_SOCKET)
	{
		switch (WSAGetLastError())
		{
		case WSANOTINITIALISED:
		case WSAENOTCONN:
		case WSAECONNABORTED:
		case WSAETIMEDOUT:
		case WSAECONNRESET:
		case WSAEINTR:
		{
			break;
		}
		default:
		{
			m_errorLog->WriteWinsockErrorMessage(true, "CSocket::Receive::recv:INVALID_SOCKET:");

			m_state = CSocket::State::E_FAILED;

			break;
		}
		}
	}

	if (m_totalBytes == SOCKET_ERROR)
	{
		switch (WSAGetLastError())
		{
		case WSANOTINITIALISED:
		case WSAENOTCONN:
		case WSAECONNABORTED:
		case WSAETIMEDOUT:
		case WSAECONNRESET:
		case WSAEINTR:
		{
			break;
		}
		default:
		{
			m_errorLog->WriteWinsockErrorMessage(true, "CSocket::Receive::recv:SOCKET_ERROR:");

			m_state = CSocket::State::E_FAILED;

			break;
		}
		}
	}

	return m_totalBytes;
}

/*
*/
bool CSocket::Send(char* data, int32_t length)
{
	m_totalBytes = send(m_socket, data, length, 0);

	if (m_totalBytes == SOCKET_ERROR)
	{
		switch (WSAGetLastError())
		{
		case WSANOTINITIALISED:
		case WSAENOTCONN:
		case WSAECONNABORTED:
		case WSAECONNRESET:
		case WSAEINTR:
		{
			break;
		}
		default:
		{
			m_errorLog->WriteWinsockErrorMessage(true, "CSocket::Send::send:");

			m_state = CSocket::State::E_FAILED;

			break;
		}
		}

		return false;
	}

	return true;
}

/*
*/
void CSocket::SetReceiveTimeout(int32_t optval)
{
	m_result = setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&optval, sizeof(int32_t));

	if (m_result == SOCKET_ERROR)
	{
		m_errorLog->WriteWinsockErrorMessage(true, "CSocket::SetTimeout::setsockopt:");

		m_state = CSocket::State::E_FAILED;
	}
}

/*
*/
bool CSocket::Shutdown()
{
	m_result = shutdown(m_socket, SD_BOTH);

	if (m_result == SOCKET_ERROR)
	{
		switch (WSAGetLastError())
		{
		case WSANOTINITIALISED:
		case WSAENOTCONN:
		case WSAEINTR:
		case WSAENOTSOCK:
		{
			break;
		}
		default:
		{
			m_errorLog->WriteWinsockErrorMessage(true, "CSocket::Shutdown:shutdown:SOCKET_ERROR");

			m_state = CSocket::State::E_FAILED;

			break;
		}
		}

		return false;
	}

	closesocket(m_socket);

	m_socket = 0;

	freeaddrinfo(m_addrResult);

	m_addrResult = 0;

	m_state = CSocket::State::E_NOT_CONNECTED;

	return true;
}

/*
*/
bool CSocket::ShutdownListen()
{
	m_result = closesocket(m_socket);

	if (m_result == SOCKET_ERROR)
	{
		switch (WSAGetLastError())
		{
		case WSANOTINITIALISED:
		case WSAENOTCONN:
		case WSAEINTR:
		case WSAENOTSOCK:
		{
			break;
		}
		default:
		{
			m_errorLog->WriteWinsockErrorMessage(true, "CSocket::Shutdown:shutdown:");

			m_state = CSocket::State::E_FAILED;

			break;
		}
		}

		return false;
	}

	m_socket = 0;

	freeaddrinfo(m_addrResult);

	m_addrResult = 0;

	m_state = CSocket::State::E_NOT_CONNECTED;

	return true;
}