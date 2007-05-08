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
/* Network server receive thread. */

#ifndef _SERVERRECVTHREAD_H_
#define _SERVERRECVTHREAD_H_

#include <core/thread.h>
#include <net/connectdata.h>
#include <net/sessiondata.h>
#include <net/servercallback.h>

#include <deque>
#include <map>
#include <list>
#include <string>
#include <boost/shared_ptr.hpp>
#include <core/boost/timer.hpp>

#define RECEIVER_THREAD_TERMINATE_TIMEOUT	200

// Notifications
#define NOTIFY_GAME_START		1

class ServerRecvState;
class SenderThread;
class ReceiverHelper;
class ServerSenderCallback;
class NetPacket;
struct GameData;

class ServerRecvThread : public Thread
{
public:
	ServerRecvThread(ServerCallback &gui);
	virtual ~ServerRecvThread();

	void Init(const std::string &pwd, const GameData &gameData);

	void AddConnection(boost::shared_ptr<ConnectData> data);
	void AddNotification(unsigned notification);

	ServerCallback &GetCallback();

protected:

	typedef std::deque<boost::shared_ptr<ConnectData> > ConnectQueue;
	typedef std::map<SOCKET, boost::shared_ptr<SessionData> > SocketSessionMap;
	typedef std::deque<unsigned> NotificationQueue;
	typedef std::list<std::pair<boost::microsec_timer, boost::shared_ptr<SessionData> > > CloseSessionList;

	// Main function of the thread.
	virtual void Main();

	void NotificationLoop();
	void CloseSessionLoop();

	SOCKET Select();

	void CleanupConnectQueue();
	void CleanupSessionMap();

	boost::shared_ptr<SessionData> GetSession(SOCKET sock);
	void AddSession(boost::shared_ptr<SessionData> sessionData);
	void SessionError(boost::shared_ptr<SessionData> sessionData, int errorCode);
	void CloseSessionDelayed(boost::shared_ptr<SessionData> sessionData);

	size_t GetCurNumberOfPlayers() const;
	bool IsPlayerConnected(const std::string &playerName) const;
	void SetSessionPlayerData(boost::shared_ptr<SessionData> sessionData, boost::shared_ptr<PlayerData> playerData);
	PlayerDataList GetPlayerDataList() const;

	int GetNextPlayerNumber() const;

	void SendError(SOCKET s, int errorCode);
	void SendToAllPlayers(boost::shared_ptr<NetPacket> packet);
	void SendToAllButOnePlayers(boost::shared_ptr<NetPacket> packet, SOCKET except);

	ServerRecvState &GetState();
	void SetState(ServerRecvState &newState);

	SenderThread &GetSender();
	ReceiverHelper &GetReceiver();

	const GameData &GetGameData() const;
	bool CheckPassword(const std::string &password) const;

	ServerSenderCallback &GetSenderCallback();

private:

	ConnectQueue m_connectQueue;
	mutable boost::mutex m_connectQueueMutex;
	ServerRecvState *m_curState;

	NotificationQueue m_notificationQueue;
	mutable boost::mutex m_notificationQueueMutex;

	SocketSessionMap m_sessionMap;
	mutable boost::mutex m_sessionMapMutex;

	CloseSessionList m_closeSessionList;

	std::auto_ptr<ReceiverHelper> m_receiver;
	std::auto_ptr<SenderThread> m_sender;

	std::auto_ptr<ServerSenderCallback> m_senderCallback;
	std::auto_ptr<GameData> m_gameData;

	std::string m_password;

	ServerCallback &m_callback;

friend class ServerRecvStateInit;
friend class ServerRecvStateStartGame;
};

#endif
