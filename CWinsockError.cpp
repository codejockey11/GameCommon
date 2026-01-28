#include "CWinsockError.h"

/*
*/
CWinsockError::CWinsockError()
{
	memset(this, 0x00, sizeof(CWinsockError));

	m_errors = new CList();

	m_defaultError = new CWinsockErrorItem(0, "WSA_UKNOWN_ERROR", "There is something wrong with the parameters of the call.");

	CWinsockError::AddItem(6, "WSA_INVALID_HANDLE", "Specified event object handle is invalid.");
	CWinsockError::AddItem(87, "WSA_INVALID_PARAMETER", "One or more parameters are invalid.");
	CWinsockError::AddItem(995, "WSA_OPERATION_ABORTED", "Overlapped operation aborted.");
	CWinsockError::AddItem(996, "WSA_IO_INCOMPLETE", "Overlapped I/O event object not in signaled state.");
	CWinsockError::AddItem(997, "WSA_IO_PENDING", "Overlapped operations will complete later.");
	CWinsockError::AddItem(10004, "WSAEINTR", "Interrupted function call.");
	CWinsockError::AddItem(10009, "WSAEBADF", "File handle is not valid.");
	CWinsockError::AddItem(10013, "WSAEACCES", "Permission denied.");
	CWinsockError::AddItem(10014, "WSAEFAULT", "Bad address.");
	CWinsockError::AddItem(10022, "WSAEINVAL", "Invalid argument.");
	CWinsockError::AddItem(10024, "WSAEMFILE", "Too many open files.");
	CWinsockError::AddItem(10035, "WSAEWOULDBLOCK", "Resource temporarily unavailable.");
	CWinsockError::AddItem(10036, "WSAEINPROGRESS", "Operation now in progress.");
	CWinsockError::AddItem(10037, "WSAEALREADY", "Operation already in progress.");
	CWinsockError::AddItem(10038, "WSAENOTSOCK", "Socket operation on nonsocket.");
	CWinsockError::AddItem(10039, "WSAEDESTADDRREQ", "Destination address required.");
	CWinsockError::AddItem(10040, "WSAEMSGSIZE", "Message too long.");
	CWinsockError::AddItem(10041, "WSAEPROTOTYPE", "Protocol wrong type for socket.");
	CWinsockError::AddItem(10042, "WSAENOPROTOOPT", "Bad protocol option.");
	CWinsockError::AddItem(10043, "WSAEPROTONOSUPPORT", "Protocol not supported.");
	CWinsockError::AddItem(10044, "WSAESOCKTNOSUPPORT", "Socket type not supported.");
	CWinsockError::AddItem(10045, "WSAEOPNOTSUPP", "Operation not supported.");
	CWinsockError::AddItem(10046, "WSAEPFNOSUPPORT", "Protocol family not supported.");
	CWinsockError::AddItem(10047, "WSAEAFNOSUPPORT", "Address family not supported by protocol family.");
	CWinsockError::AddItem(10048, "WSAEADDRINUSE", "Address already in use.");
	CWinsockError::AddItem(10049, "WSAEADDRNOTAVAIL", "Cannot assign requested address.");
	CWinsockError::AddItem(10050, "WSAENETDOWN", "Network is down.");
	CWinsockError::AddItem(10051, "WSAENETUNREACH", "Network is unreachable.");
	CWinsockError::AddItem(10052, "WSAENETRESET", "Network dropped connection on reset.");
	CWinsockError::AddItem(10053, "WSAECONNABORTED", "Software caused connection abort.");
	CWinsockError::AddItem(10054, "WSAECONNRESET", "Connection reset by peer.");
	CWinsockError::AddItem(10055, "WSAENOBUFS", "No buffer space available.");
	CWinsockError::AddItem(10056, "WSAEISCONN", "Socket is already connected.");
	CWinsockError::AddItem(10057, "WSAENOTCONN", "Socket is not connected.");
	CWinsockError::AddItem(10058, "WSAESHUTDOWN", "Cannot send after socket shutdown.");
	CWinsockError::AddItem(10059, "WSAETOOMANYREFS", "Too many references.");
	CWinsockError::AddItem(10060, "WSAETIMEDOUT", "Connection timed out.");
	CWinsockError::AddItem(10061, "WSAECONNREFUSED", "Connection refused.");
	CWinsockError::AddItem(10062, "WSAELOOP", "Cannot translate name.");
	CWinsockError::AddItem(10063, "WSAENAMETOOLONG", "Name too long.");
	CWinsockError::AddItem(10064, "WSAEHOSTDOWN", "Host is down.");
	CWinsockError::AddItem(10065, "WSAEHOSTUNREACH", "No route to host.");
	CWinsockError::AddItem(10066, "WSAENOTEMPTY", "Directory not empty.");
	CWinsockError::AddItem(10067, "WSAEPROCLIM", "Too many processes.");
	CWinsockError::AddItem(10068, "WSAEUSERS", "User quota exceeded.");
	CWinsockError::AddItem(10069, "WSAEDQUOT", "Disk quota exceeded.");
	CWinsockError::AddItem(10070, "WSAESTALE", "Stale file handle reference.");
	CWinsockError::AddItem(10071, "WSAEREMOTE", "Item is remote.");
	CWinsockError::AddItem(10091, "WSASYSNOTREADY", "Network subsystem is unavailable.");
	CWinsockError::AddItem(10092, "WSAVERNOTSUPPORTED", "Winsock.dll version out of range.");
	CWinsockError::AddItem(10093, "WSANOTINITIALISED", "Successful WSAStartup not yet performed.");
	CWinsockError::AddItem(10101, "WSAEDISCON", "Graceful shutdown in progress.");
	CWinsockError::AddItem(10102, "WSAENOMORE", "No more results.");
	CWinsockError::AddItem(10103, "WSAECANCELLED", "Call has been canceled.");
	CWinsockError::AddItem(10104, "WSAEINVALIDPROCTABLE", "Procedure call table is invalid.");
	CWinsockError::AddItem(10105, "WSAEINVALIDPROVIDER", "Service provider is invalid.");
	CWinsockError::AddItem(10106, "WSAEPROVIDERFAILEDINIT", "Service provider failed to initialize.");
	CWinsockError::AddItem(10107, "WSASYSCALLFAILURE", "System call failure.");
	CWinsockError::AddItem(10108, "WSASERVICE_NOT_FOUND", "Service not found.");
	CWinsockError::AddItem(10109, "WSATYPE_NOT_FOUND", "Class type not found.");
	CWinsockError::AddItem(10110, "WSA_E_NO_MORE", "No more results.");
	CWinsockError::AddItem(10111, "WSA_E_CANCELLED", "Call was canceled.");
	CWinsockError::AddItem(10112, "WSAEREFUSED", "Database query was refused.");
	CWinsockError::AddItem(11001, "WSAHOST_NOT_FOUND", "Host not found.");
	CWinsockError::AddItem(11002, "WSATRY_AGAIN", "Nonauthoritative host not found.");
	CWinsockError::AddItem(11003, "WSANO_RECOVERY", "This is a nonrecoverable error.");
	CWinsockError::AddItem(11004, "WSANO_DATA", "Valid name, no data record of requested type.");
	CWinsockError::AddItem(11005, "WSA_QOS_RECEIVERS", "QoS receivers.");
	CWinsockError::AddItem(11006, "WSA_QOS_SENDERS", "QoS senders.");
	CWinsockError::AddItem(11007, "WSA_QOS_NO_SENDERS", "No QoS senders.");
	CWinsockError::AddItem(11008, "WSA_QOS_NO_RECEIVERS", "QoS no receivers.");
	CWinsockError::AddItem(11009, "WSA_QOS_REQUEST_CONFIRMED", "QoS request confirmed.");
	CWinsockError::AddItem(11010, "WSA_QOS_ADMISSION_FAILURE", "QoS admission error.");
	CWinsockError::AddItem(11011, "WSA_QOS_POLICY_FAILURE", "QoS policy failure.");
	CWinsockError::AddItem(11012, "WSA_QOS_BAD_STYLE", "QoS bad style.");
	CWinsockError::AddItem(11013, "WSA_QOS_BAD_OBJECT", "QoS bad object.");
	CWinsockError::AddItem(11014, "WSA_QOS_TRAFFIC_CTRL_ERROR", "QoS traffic control error.");
	CWinsockError::AddItem(11015, "WSA_QOS_GENERIC_ERROR", "QoS generic error.");
	CWinsockError::AddItem(11016, "WSA_QOS_ESERVICETYPE", "QoS service type error.");
	CWinsockError::AddItem(11017, "WSA_QOS_EFLOWSPEC", "QoS flowspec error.");
	CWinsockError::AddItem(11018, "WSA_QOS_EPROVSPECBUF", "Invalid QoS provider buffer.");
	CWinsockError::AddItem(11019, "WSA_QOS_EFILTERSTYLE", "Invalid QoS filter style.");
	CWinsockError::AddItem(11020, "WSA_QOS_EFILTERTYPE", "Invalid QoS filter type.");
	CWinsockError::AddItem(11021, "WSA_QOS_EFILTERCOUNT", "Incorrect QoS filter count.");
	CWinsockError::AddItem(11022, "WSA_QOS_EOBJLENGTH", "Invalid QoS object length.");
	CWinsockError::AddItem(11023, "WSA_QOS_EFLOWCOUNT", "Incorrect QoS flow count.");
	CWinsockError::AddItem(11024, "WSA_QOS_EUNKOWNPSOBJ", "Unrecognized QoS object.");
	CWinsockError::AddItem(11025, "WSA_QOS_EPOLICYOBJ", "Invalid QoS policy object.");
	CWinsockError::AddItem(11026, "WSA_QOS_EFLOWDESC", "Invalid QoS flow descriptor.");
	CWinsockError::AddItem(11027, "WSA_QOS_EPSFLOWSPEC", "Invalid QoS provider - specific flowspec.");
	CWinsockError::AddItem(11028, "WSA_QOS_EPSFILTERSPEC", "Invalid QoS provider - specific filterspec.");
	CWinsockError::AddItem(11029, "WSA_QOS_ESDMODEOBJ", "Invalid QoS shape discard mode object.");
	CWinsockError::AddItem(11030, "WSA_QOS_ESHAPERATEOBJ", "Invalid QoS shaping rate object.");
	CWinsockError::AddItem(11031, "WSA_QOS_RESERVED_PETYPE", "Reserved policy QoS element type.");
}

/*
*/
CWinsockError::~CWinsockError()
{
	m_node = m_errors->m_list;

	while ((m_node) && (m_node->m_object))
	{
		m_winsockErrorItem = (CWinsockErrorItem*)m_node->m_object;

		SAFE_DELETE(m_winsockErrorItem);

		m_node = m_errors->Delete(m_node);
	}

	SAFE_DELETE(m_errors);

	SAFE_DELETE(m_defaultError);
}

/*
*/
void CWinsockError::AddItem(int32_t number, const char* code, const char* message)
{
	m_winsockErrorItem = new CWinsockErrorItem(number, code, message);

	m_errors->Append(m_winsockErrorItem, m_winsockErrorItem->m_nbr);
}

/*
*/
CWinsockErrorItem* CWinsockError::GetError(int32_t error)
{
	m_node = m_errors->Search(error);

	if (m_node)
	{
		return (CWinsockErrorItem*)m_node->m_object;
	}

	return m_defaultError;
}