#include "APIHelp.h"
#include "BaseAPI.h"
#include "EntityAPI.h"
#include "PlayerAPI.h"
#include "ContainerAPI.h"
#include "NbtAPI.h"
#include <Kernel/Entity.h>
#include <Kernel/Container.h>
using namespace script;

//////////////////// Class Definition ////////////////////

ClassDefine<EntityClass> EntityClassBuilder =
    defineClass<EntityClass>("LXL_Entity")
        .constructor(nullptr)
        .instanceFunction("getRawPtr", &EntityClass::getRawPtr)

        .instanceProperty("name", &EntityClass::getName)
        .instanceProperty("type", &EntityClass::getType)
        .instanceProperty("id", &EntityClass::getId)
        .instanceProperty("pos", &EntityClass::getPos)
        .instanceProperty("blockPos", &EntityClass::getBlockPos)
        .instanceProperty("maxHealth", &EntityClass::getMaxHealth)
        .instanceProperty("health", &EntityClass::getHealth)
        .instanceProperty("inAir", &EntityClass::getInAir)
        .instanceProperty("inWater", &EntityClass::getInWater)
        .instanceProperty("speed",&EntityClass::getSpeed)

        .instanceFunction("teleport", &EntityClass::teleport)
        .instanceFunction("kill", &EntityClass::kill)
        .instanceFunction("hurt", &EntityClass::hurt)
        .instanceFunction("setOnFire", &EntityClass::setOnFire)
        .instanceFunction("isPlayer", &EntityClass::isPlayer)
        .instanceFunction("toPlayer", &EntityClass::toPlayer)
        .instanceFunction("getArmor", &EntityClass::getArmor)
        .instanceFunction("hasContainer", &EntityClass::hasContainer)
        .instanceFunction("getContainer", &EntityClass::getContainer)
        .instanceFunction("refreshItems", &EntityClass::refreshItems)
        .instanceFunction("setNbt", &EntityClass::setNbt)
        .instanceFunction("getNbt", &EntityClass::getNbt)
        .instanceFunction("addTag", &EntityClass::addTag)
        .instanceFunction("removeTag", &EntityClass::removeTag)
        .instanceFunction("hasTag", &EntityClass::hasTag)
        .instanceFunction("getAllTags", &EntityClass::getAllTags)

        //For Compatibility
        .instanceFunction("setTag", &EntityClass::setNbt)
        .instanceFunction("getTag", &EntityClass::getNbt)
        .build();


//////////////////// Classes ////////////////////

//生成函数
Local<Object> EntityClass::newEntity(Actor *p)
{
    auto newp = new EntityClass(p);
    return newp->getScriptObject();
}
Local<Object> EntityClass::newEntity(WActor p)
{
    return EntityClass::newEntity(p.v);
}
Actor* EntityClass::extractEntity(Local<Value> v)
{
    if(EngineScope::currentEngine()->isInstanceOf<EntityClass>(v))
        return EngineScope::currentEngine()->getNativeInstance<EntityClass>(v)->get();
    else
        return nullptr;
}

//成员函数
void EntityClass::set(Actor* actor)
{
    __try
    {
        id = actor->getUniqueID();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        isValid = false;
    }
}

Actor* EntityClass::get()
{
    if (!isValid)
        return nullptr;
    else
        return Raw_GetEntityByUniqueId(id);
}

Local<Value> EntityClass::getRawPtr(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();
        else
            return Number::newNumber((intptr_t)entity);
    }
    CATCH("Fail in getRawPtr!")
}

Local<Value> EntityClass::getName()
{ 
    try{
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return String::newString(Raw_GetEntityName(entity));
    }
    CATCH("Fail in getEntityName!")
}

Local<Value> EntityClass::getType()
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return String::newString(Raw_GetEntityTypeName(entity));
    }
    CATCH("Fail in getEntityType!")
}

Local<Value> EntityClass::getId()
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Number::newNumber(Raw_GetEntityTypeId(entity));
    }
    CATCH("Fail in getEntityId!")
}

Local<Value> EntityClass::getPos()
{ 
    try{
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return FloatPos::newPos(Raw_GetEntityPos(entity));
    }
    CATCH("Fail in GetEntityPos!")
}

Local<Value> EntityClass::getBlockPos()
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return IntPos::newPos(Raw_GetEntityBlockPos(entity));
    }
    CATCH("Fail in GetEntityBlockPos!")
}

Local<Value> EntityClass::getMaxHealth()
{
    try{
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Number::newNumber(Raw_GetMaxHealth(entity));
    }
    CATCH("Fail in GetMaxHealth!")
}

Local<Value> EntityClass::getHealth()
{
    try{
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Number::newNumber(Raw_GetHealth(entity));
    }
    CATCH("Fail in GetHealth!")
}

Local<Value> EntityClass::getInAir()
{
    try{
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_GetIsInAir(entity));
    }
    CATCH("Fail in getInAir!")
}

Local<Value> EntityClass::getInWater()
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_GetIsInWater(entity));
    }
    CATCH("Fail in getInWater!")
}

Local<Value> EntityClass::getSpeed()
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Number::newNumber(Raw_GetSpeed(entity));
    }
    CATCH("Fail in getSpeed!")
}

Local<Value> EntityClass::teleport(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    if (args.size() == 4)
    {
        CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
        CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
        CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
        CHECK_ARG_TYPE(args[3], ValueKind::kNumber);
    }
    
    try{
        FloatVec4 pos;

        if (args.size() == 1)
        {
            if (IsInstanceOf<IntPos>(args[0]))
            {
                // IntPos
                IntPos* posObj = IntPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos.x = posObj->x;
                    pos.y = posObj->y;
                    pos.z = posObj->z;
                    pos.dim = posObj->dim;
                }
            }
            else if (IsInstanceOf<FloatPos>(args[0]))
            {
                // FloatPos
                FloatPos* posObj = FloatPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = *posObj;
                }
            }
            else
            {
                ERROR("Wrong type of argument in teleport!");
                return Local<Value>();
            }
        }
        else if (args.size() == 4)
        {
            // number pos
            CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[3], ValueKind::kNumber);

            pos.x = args[0].asNumber().toFloat();
            pos.y = args[1].asNumber().toFloat();
            pos.z = args[2].asNumber().toFloat();
            pos.dim = args[3].toInt();
        }
        else
        {
            ERROR("Wrong number of arguments in teleport!");
            return Local<Value>();
        }
        
        Actor* entity = get();
        if (!entity)
            return Local<Value>();
        return Boolean::newBoolean(Raw_TeleportEntity(entity,pos));
    }
    CATCH("Fail in teleportEntity!")
}

Local<Value> EntityClass::kill(const Arguments& args)
{
    try{
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_KillEntity(entity));
    }
    CATCH("Fail in killEntity!")
}

Local<Value> EntityClass::isPlayer(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_IsPlayer(entity));
    }
    CATCH("Fail in isPlayer!")
}

Local<Value> EntityClass::toPlayer(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        auto pl = Raw_ToPlayer(entity);
        if (!pl)
            return Local<Value>();
        else
            return PlayerClass::newPlayer(pl);
    }
    CATCH("Fail in toPlayer!")
}

Local<Value> EntityClass::getArmor(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return ContainerClass::newContainer(Raw_GetArmor(entity));
    }
    CATCH("Fail in getArmor!");
}

Local<Value> EntityClass::refreshItems(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RefreshItems(entity));
    }
    CATCH("Fail in refreshItems!");
}

Local<Value> EntityClass::hasContainer(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_HasContainer(Raw_GetEntityPos(entity)));
    }
    CATCH("Fail in hasContainer!");
}

Local<Value> EntityClass::getContainer(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        Container* container = Raw_GetContainer(Raw_GetEntityPos(entity));
        return container ? ContainerClass::newContainer(container) : Local<Value>();
    }
    CATCH("Fail in getContainer!");
}

Local<Value> EntityClass::hurt(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        int damage = args[0].toInt();
        return Boolean::newBoolean(Raw_HurtEntity(entity, damage));
    }
    CATCH("Fail in hurt!");
}

Local<Value> EntityClass::setOnFire(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        int time = args[0].toInt();
        bool result = Raw_SetOnFire(entity, time);
        return Boolean::newBoolean(result);
    }
    CATCH("Fail in setOnFire!")
}

Local<Value> EntityClass::getNbt(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return NbtCompound::newNBT(Tag::fromActor(entity));
    }
    CATCH("Fail in getNbt!")
}

Local<Value> EntityClass::setNbt(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);

    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        auto nbt = NbtCompound::extractNBT(args[0]);
        if (!nbt)
            return Local<Value>();    //Null

        return Boolean::newBoolean(nbt->setActor(entity));
    }
    CATCH("Fail in setNbt!")
}

Local<Value> EntityClass::addTag(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_AddTag(entity,args[0].toStr()));
    }
    CATCH("Fail in addTag!");
}

Local<Value> EntityClass::removeTag(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_RemoveTag(entity, args[0].toStr()));
    }
    CATCH("Fail in removeTag!");
}

Local<Value> EntityClass::hasTag(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        return Boolean::newBoolean(Raw_EntityHasTag(entity, args[0].toStr()));
    }
    CATCH("Fail in hasTag!");
}

Local<Value> EntityClass::getAllTags(const Arguments& args)
{
    try {
        Actor* entity = get();
        if (!entity)
            return Local<Value>();

        auto res = Raw_EntityGetAllTags(entity);
        Local<Array> arr = Array::newArray();
        for (auto& tag : res)
            arr.add(String::newString(tag));
        return arr;
    }
    CATCH("Fail in getAllTags!");
}

Local<Value> GetAllEntities(const Arguments& args) {
    try {
       auto entityList = Raw_getAllEntities();
       auto arr = Array::newArray();
       for (auto i : entityList) {
           arr.add(EntityClass::newEntity(i));
       }
       return arr;
    }
    CATCH("Fail in GetAllEntities");
}

Local<Value> SpawnMob(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        string name = args[0].toStr();
        FloatVec4 pos;

        if (args.size() == 2)
        {
            if (IsInstanceOf<IntPos>(args[1]))
            {
                // IntPos
                IntPos* posObj = IntPos::extractPos(args[1]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos.x = posObj->x;
                    pos.y = posObj->y;
                    pos.z = posObj->z;
                    pos.dim = posObj->dim;
                }
            }
            else if (IsInstanceOf<FloatPos>(args[1]))
            {
                // FloatPos
                FloatPos* posObj = FloatPos::extractPos(args[1]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = *posObj;
                }
            }
            else
            {
                ERROR("Wrong type of argument in SpawnMob!");
                return Local<Value>();
            }
        }
        else if (args.size() == 5)
        {
            // Number Pos
            CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[3], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[4], ValueKind::kNumber);
            pos = { args[1].asNumber().toFloat(), args[2].asNumber().toFloat(), args[3].asNumber().toFloat(), args[4].toInt() };
        }
        else
        {
            ERROR("Wrong number of arguments in SpawnMob!");
            return Local<Value>();
        }

        auto entity = Raw_SpawnMob(name,pos);
        if (!entity)
            return Local<Value>();    //Null
        else
            return EntityClass::newEntity(entity);
    }
    CATCH("Fail in SpawnMob!");
}

Local<Value> Explode(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 6);

    try {
        FloatVec4 pos;
        int beginIndex;
        if (args.size() == 6)
        {
            // PosObj
            beginIndex = 1;

            if (IsInstanceOf<IntPos>(args[0]))
            {
                // IntPos
                IntPos* posObj = IntPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos.x = posObj->x;
                    pos.y = posObj->y;
                    pos.z = posObj->z;
                    pos.dim = posObj->dim;
                }
            }
            else if (IsInstanceOf<FloatPos>(args[0]))
            {
                // FloatPos
                FloatPos* posObj = FloatPos::extractPos(args[0]);
                if (posObj->dim < 0)
                    return Boolean::newBoolean(false);
                else
                {
                    pos = *posObj;
                }
            }
            else
            {
                ERROR("Wrong type of argument in Explode!");
                return Local<Value>();
            }
        }
        else if (args.size() == 9)
        {
            // Number Pos
            beginIndex = 4;
            CHECK_ARG_TYPE(args[0], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[1], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[2], ValueKind::kNumber);
            CHECK_ARG_TYPE(args[3], ValueKind::kNumber);
            pos = { args[0].asNumber().toFloat(), args[1].asNumber().toFloat(), args[2].asNumber().toFloat(), args[3].toInt() };
        }
        else
        {
            ERROR("Wrong number of arguments in Explode!");
            return Local<Value>();
        }

        auto source = EntityClass::extractEntity(args[beginIndex + 0]); //Can be nullptr
        
        CHECK_ARG_TYPE(args[beginIndex + 1], ValueKind::kNumber);
        CHECK_ARG_TYPE(args[beginIndex + 2], ValueKind::kNumber);
        CHECK_ARG_TYPE(args[beginIndex + 3], ValueKind::kBoolean);
        CHECK_ARG_TYPE(args[beginIndex + 4], ValueKind::kBoolean);

        float power = args[beginIndex + 1].asNumber().toFloat();
        float range = args[beginIndex + 2].asNumber().toFloat();
        bool isDestroy = args[beginIndex + 3].asBoolean().value();
        bool isFire = args[beginIndex + 4].asBoolean().value();

        return Boolean::newBoolean(Raw_Explode(pos, source, power, range, isDestroy, isFire));
    }
    CATCH("Fail in Explode!");
}