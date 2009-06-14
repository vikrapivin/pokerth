/***************************************************************************
 *   Copyright (C) 2007 by Lothar May                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/* Context of network client. */

#ifndef _CLIENTCONTEXT_H_
#define _CLIENTCONTEXT_H_

#include <boost/shared_ptr.hpp>

#include <net/receivebuffer.h>
#include <net/sessiondata.h>


class ClientContext
{
public:
	ClientContext();
	virtual ~ClientContext();

	boost::shared_ptr<SessionData> GetSessionData() const;
	void SetSessionData(boost::shared_ptr<SessionData> sessionData);
	boost::shared_ptr<boost::asio::ip::tcp::resolver> GetResolver() const;
	void SetResolver(boost::shared_ptr<boost::asio::ip::tcp::resolver> resolver);
	int GetProtocol() const
	{return m_protocol;}
	void SetProtocol(int protocol)
	{m_protocol = protocol;}
	int GetAddrFamily() const
	{return m_addrFamily;}
	void SetAddrFamily(int addrFamily)
	{m_addrFamily = addrFamily;}
	const std::string &GetServerAddr() const
	{return m_serverAddr;}
	void SetServerAddr(const std::string &serverAddr)
	{m_serverAddr = serverAddr;}
	const std::string &GetServerListUrl() const
	{return m_serverListUrl;}
	void SetServerListUrl(const std::string &serverListUrl)
	{m_serverListUrl = serverListUrl;}
	bool GetUseServerList() const
	{return m_useServerList;}
	void SetUseServerList(bool use)
	{m_useServerList = use;}
	unsigned GetServerPort() const
	{return m_serverPort;}
	void SetServerPort(unsigned serverPort)
	{m_serverPort = serverPort;}
	const std::string &GetAvatarServerAddr() const
	{return m_avatarServerAddr;}
	void SetAvatarServerAddr(const std::string &avatarServerAddr)
	{m_avatarServerAddr = avatarServerAddr;}
	const std::string &GetPassword() const
	{return m_password;}
	void SetPassword(const std::string &password)
	{m_password = password;}
	const std::string &GetPlayerName() const
	{return m_playerName;}
	void SetPlayerName(const std::string &playerName)
	{m_playerName = playerName;}
	const std::string &GetAvatarFile() const
	{return m_avatarFile;}
	void SetAvatarFile(const std::string &avatarFile)
	{m_avatarFile = avatarFile;}
	const std::string &GetCacheDir() const
	{return m_cacheDir;}
	void SetCacheDir(const std::string &cacheDir)
	{m_cacheDir = cacheDir;}
	bool GetSubscribeLobbyMsg() const
	{return m_hasSubscribedLobbyMsg;}
	void SetSubscribeLobbyMsg(bool setSubscribe)
	{m_hasSubscribedLobbyMsg = setSubscribe;}

	ReceiveBuffer &GetReceiveBuffer()
	{return m_receiveBuffer;}

private:
	boost::shared_ptr<SessionData> m_sessionData;
	boost::shared_ptr<boost::asio::ip::tcp::resolver> m_resolver;
	int					m_protocol;
	int					m_addrFamily;
	std::string			m_serverAddr;
	std::string			m_serverListUrl;
	bool				m_useServerList;
	unsigned			m_serverPort;
	std::string			m_avatarServerAddr;
	std::string			m_password;
	std::string			m_playerName;
	std::string			m_avatarFile;
	std::string			m_cacheDir;
	bool				m_hasSubscribedLobbyMsg;
	ReceiveBuffer		m_receiveBuffer;
};

#endif
