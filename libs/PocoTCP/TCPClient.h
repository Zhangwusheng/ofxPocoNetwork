#pragma once

#include "ofMain.h"
#include "Poco/Net/Socket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/StreamSocket.h"
#include "TCPConnectionHandler.h"


namespace ofxPocoNetwork {
    
class TCPClient {
public:
    
    TCPClient();
    virtual ~TCPClient();
    
    void connect(string ipAddr, int port, MessageFraming protocol=FRAME_HEADER_AND_MESSAGE);
    bool isConnected();
    
    void disconnect();
    
    // doesnt need listeners for added/removed as it's created internally
    TCPClientConnectionHandler* socketHandler;
    void onClientRemoved(const void* socket);
    
    // the connect timeout only occurs on the first run atm
    void setConnectTimeout(int timeoutInSeconds);
    //void setReceiveTimeout(int timeoutInSeconds);
    //void setSendTimeout(int timeoutInSeconds);
    //void setPollTimeout(int timeoutInSeconds);
    
    
    // for TYPE_FIXED_SIZE only
    void setFixedReceiveSize(int s);
    
    // send (non blocking)
    void sendMessage(string msg);
    void sendMessage(ofBuffer& msg);
    
    // receive (non blocking)
    bool hasWaitingMessages();
    bool getNextMessage(ofBuffer& buffer);
    bool getNextMessage(string& buffer);
    
protected:
    
    bool connected;
    int fixedReceiveSize;
    
    Poco::Net::SocketAddress* socketAddress;
    Poco::Net::StreamSocket* socketStream;
    Poco::Thread thread;
    
    Poco::Timespan connectTimeout;
    //Poco::Timespan receiveTimeout;
    //Poco::Timespan sendTimeout;
    //Poco::Timespan pollTimeout;
};

} // namespace ofxPocoNetwork