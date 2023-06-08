#include "canTranslator.hpp"
#include <iostream>
#include <map>

canTranslator::canTranslator(int csPin) : pin(csPin), mcp2515(csPin)
{
    CAN_setup();
};

// default destructor
canTranslator::~canTranslator(){};

void canTranslator::CAN_setup()
{
    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();
}

std::string canTranslator::canframeToProductInfo(struct can_frame *msg)
{
    std::string productInfo = "";
    for (int i = 0; i < msg->can_dlc; ++i)
    {
        productInfo += (char)msg->data[i];
    }
    return productInfo;
}

void canTranslator::alterWorkspace(uint8_t newWS, long recentCanId)
{
    struct can_frame response;

    response.can_dlc = 2;
    response.can_id = (CAN_EFF_FLAG | recentCanId);

    response.data[0] = newWS;
    mcp2515.sendMessage(&response);
}

bool canTranslator::workspaceRequestReceived(struct can_frame *msg)
{
    if (mcp2515.readMessage(msg) == MCP2515::ERROR_OK)
    {
        ByteToLong bt;
        bt.myLong = msg->can_id;
        if (bt.byte[1] == MSG_WS_REQUEST)
        {
            return true;
        }
    }
    return false;
}

void canTranslator::sendStartMessage()
{
    sendMessage(deviceID, MSG_START);
}

void canTranslator::sendMessage(uint8_t ws, MSG_TYPE type)
{
    struct can_frame startMsg;
    startMsg.can_dlc = 0;
    ByteToLong bt;

    bt.byte[0] = ws;
    bt.byte[1] = type;
    bt.byte[2] = 0;
    bt.byte[3] = 0;

    startMsg.can_id = CAN_EFF_FLAG | bt.myLong;

    mcp2515.sendMessage(&startMsg);
}

void canTranslator::sendMessage(uint8_t ws, MSG_TYPE type, std::vector<uint8_t> data)
{
    struct can_frame startMsg;
    startMsg.can_dlc = data.size();

    std::cout << data.size() << std::endl;

    ByteToLong bt;

    bt.byte[0] = ws;
    bt.byte[1] = type;
    bt.byte[2] = 0;
    bt.byte[3] = 0;

    for (int i = 0; i < startMsg.can_dlc; ++i)
    {
        startMsg.data[i] = data.at(i);
    }

    startMsg.can_id = CAN_EFF_FLAG | bt.myLong;

    mcp2515.sendMessage(&startMsg);
}

bool canTranslator::dockingRequestReceived()
{
    ByteToLong bt;
    bt.myLong = msg.can_id;

    int ws = bt.byte[0];
    MSG_TYPE type = (MSG_TYPE)bt.byte[1];

    return (type == MSG_DOCKED_DONE);
}

bool canTranslator::getIncomingMessageInfo(MSG_TYPE *type, short *workspace)
{
    if (mcp2515.readMessage(&this->msg) == MCP2515::ERROR_OK)
    {
        ByteToLong bt;
        bt.myLong = msg.can_id;

        *workspace = (short)bt.byte[0];
        *type = (MSG_TYPE)bt.byte[1];

        return true;
    }
    return false;
}

bool canTranslator::awaitStartupMessage(short *subscribedWorkspace)
{
    MSG_TYPE type = MSG_DOCKING_CANCELLED;
    return (getIncomingMessageInfo(&type, subscribedWorkspace) && type == MSG_UNDOCKED);
}

int canTranslator::getStoredWorkspace()
{
    ByteToLong bt;
    bt.myLong = msg.can_id;

    return bt.byte[0];
}
struct can_frame* canTranslator::getStoredMessage(){
    return &msg;
}

void canTranslator::clearMsgBuffer()
{
    msg = can_frame();
}
