#ifndef CANTRANSLATOR_HPP_
#define CANTRANSLATOR_HPP_

#include "mcp2515.hpp"
#include <bcm2835.h>

class canTranslator
{
public:
    canTranslator(int csPin);

    ~canTranslator();

    union ByteToLong
    {
        uint8_t byte[4];
        unsigned long myLong;
    };

    enum MSG_TYPE
    {
        MSG_START = 0,
        MSG_WS_REQUEST = 1,
        MSG_WS_RESPONSE = 2,
        MSG_DOCKED_SENDING = 3,
        MSG_DOCKED_DONE = 4,
        MSG_UNDOCKED = 5,
        MSG_DOCKING_CANCELLED = 6,
        MSG_DOCKING_SUCCESFUL = 7
    };

    const uint8_t deviceID = 0;

    MCP2515 mcp2515;

    void CAN_setup();

    std::string canframeToProductInfo(struct can_frame *msg);
    void alterWorkspace(uint8_t newWS, long recentCanId);
    bool workspaceRequestReceived(struct can_frame *msg);
    bool dockingRequestReceived();
    void sendStartMessage();
    void sendMessage(uint8_t ws, MSG_TYPE type);
    void sendMessage(uint8_t ws, MSG_TYPE type, std::vector<uint8_t> data);

    int getStoredWorkspace();
        struct can_frame* getStoredMessage();

    bool getIncomingMessageInfo(MSG_TYPE *type, short *workspace);
    bool awaitStartupMessage(short *subscribedWorkspace);
    // void awaitIncomingMessages(struct can_frame *msg);
    void clearMsgBuffer();


private:
    int pin;
    struct can_frame msg;
};

#endif /* CANTRANSLATOR_HPP_ */