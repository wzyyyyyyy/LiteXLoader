#pragma once
#include <ScriptX/ScriptX.h>
using namespace script;

#include <Kernel/Global.h>
#include <string>

//////////////////// Classes ////////////////////
class BlockActor;
class BlockEntityClass : public ScriptClass
{
private:
    BlockActor* blockEntity;
    int dim;

public:
    explicit BlockEntityClass(BlockActor* be,int dim);

    BlockActor* get()
    {
        return blockEntity;
    }

    static Local<Object> newBlockEntity(BlockActor* be, int dim);
    static BlockActor* extractBlockEntity(Local<Value> v);
    Local<Value> getRawPtr(const Arguments& args);

    Local<Value> getPos();
    Local<Value> getType();

    Local<Value> getNbt(const Arguments& args);
    Local<Value> setNbt(const Arguments& args);
    Local<Value> getBlock(const Arguments& args);
};