#include <iostream>
#include <Cstring>
using namespace std;
#ifndef PACKET_H
#define PACKET_H
#define BUFFER_SIZE 20 * 1024
#define BUFFERFILE_SIZE BUFFER_SIZE - 2 * sizeof(int)
class Serializable
{
    virtual size_t serialize_size() const = 0;
    virtual void serialize(char*) const = 0;
    virtual void deserialize(const char*) = 0;
};
enum Headers
{
    Start,
    Chunk,
    StringMessage,
    Login,
    HeartBit
};
struct Packet : public Serializable
{
    Headers Type;
    size_t serialize_size() const
    {
        return sizeof(Packet);
    }
    void serialize(char* dataOut) const
    {
        memcpy(dataOut, (void*)this, sizeof(Packet));
    }
    void deserialize(const char* dataIn)
    {
        memcpy(this, dataIn, sizeof(Packet));
    }
};
struct FilePacket : public  Packet
{
    int QueueID;
    int QueueIndex;
    int Read;
    char FileBuffer[BUFFERFILE_SIZE];
    size_t serialize_size() const override
    {
        return sizeof(FilePacket);
    }
    void serialize(char* dataOut) const override
    {
        memcpy(dataOut, (void*)this, sizeof(FilePacket));
    }
    void deserialize(const char* dataIn) override
    {
        memcpy(this, dataIn, sizeof(FilePacket));
    }
};
#endif // !PACKET_H

int main()
{
    Packet pk ;
    pk.Type = Headers::Chunk;
    char buff[sizeof(Packet)];
    pk.serialize(buff);
    cout << "serialized" << endl;
    Packet pk2;
    pk2.deserialize(buff);
    cout << pk2.Type << endl;
}
