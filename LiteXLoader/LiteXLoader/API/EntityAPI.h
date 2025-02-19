#pragma once
#include <ScriptX/ScriptX.h>
using namespace script;

//////////////////// Classes ////////////////////
class Actor;
class EntityClass : public ScriptClass
{
private:
    ActorUniqueID id;
    bool isValid = true;

public:
	explicit EntityClass(Actor *p)
        :ScriptClass(ScriptClass::ConstructFromCpp<EntityClass>{})
    {
        set(p);
    }

    void set(Actor* actor);
    Actor* get();

    static Local<Object> newEntity(Actor *p);
    static Local<Object> newEntity(WActor p);
    static Actor* extractEntity(Local<Value> v);
    Local<Value> getRawPtr(const Arguments& args);

    Local<Value> getName();
    Local<Value> getType();
    Local<Value> getId();
    Local<Value> getPos();
    Local<Value> getBlockPos();
    Local<Value> getMaxHealth();
    Local<Value> getHealth();
    Local<Value> getInAir();
    Local<Value> getInWater();
    Local<Value> getSpeed();

    Local<Value> teleport(const Arguments& args);
    Local<Value> kill(const Arguments& args);
    Local<Value> hurt(const Arguments& args);
    Local<Value> setOnFire(const Arguments& args);

    Local<Value> isMob(const Arguments& args);
    Local<Value> isPlayer(const Arguments& args);
    Local<Value> toPlayer(const Arguments& args);
    Local<Value> getArmor(const Arguments& args);
    Local<Value> hasContainer(const Arguments& args);
    Local<Value> getContainer(const Arguments& args);
    Local<Value> refreshItems(const Arguments& args);
    
    Local<Value> getNbt(const Arguments& args);
    Local<Value> setNbt(const Arguments& args);
    Local<Value> addTag(const Arguments& args);
    Local<Value> removeTag(const Arguments& args);
    Local<Value> hasTag(const Arguments& args);
    Local<Value> getAllTags(const Arguments& args);
};

//////////////////// APIs ////////////////////
Local<Value> GetAllEntities(const Arguments& args);

Local<Value> SpawnMob(const Arguments& args);
Local<Value> Explode(const Arguments& args);