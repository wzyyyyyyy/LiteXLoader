﻿#include "Global.h"
#include "NBT.h"
#include "Data.h"
#include <vector>
#include <map>
#include <sstream>
#include "ThirdParty.h"
using namespace std;

//////////////////// NBT Class ////////////////////

char& Tag::asByte()
{
	return *(char*)((uintptr_t)this + 8);
}

short& Tag::asShort()
{
	return *(short*)((uintptr_t)this + 8);
}

int& Tag::asInt()
{
	return *(int*)((uintptr_t)this + 8);
}

__int64& Tag::asLong()
{
	return *(__int64*)((uintptr_t)this + 8);
}

float& Tag::asFloat()
{
	return *(float*)((uintptr_t)this + 8);
}

double& Tag::asDouble()
{
	return *(double*)((uintptr_t)this + 8);
}

std::string& Tag::asString()
{
	return *(string*)((uintptr_t)this + 8);
}

vector<Tag*> &Tag::asList()
{
	return *(vector<Tag*>*)((uintptr_t)this + 8);
}

map<string, Tag> &Tag::asCompound()
{
	return *(map<string,Tag>*)((uintptr_t)this + 8);
}

TagMemoryChunk& Tag::asByteArray()
{
    return *(TagMemoryChunk*)((uintptr_t)this + 8);
}

Tag* Tag::createTag(TagType t)
{
	Tag* tag = 0;
	SymCall("?newTag@Tag@@SA?AV?$unique_ptr@VTag@@U?$default_delete@VTag@@@std@@@std@@W4Type@1@@Z",
		void, Tag**, TagType)(&tag, t);
	return tag;
}

char Tag::getTagType() {
    __try
    {
        return ((*(__int64(__fastcall**)(const struct Tag*))(*(uintptr_t*)this + 40i64))(this));
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return -1;
    }
}

void Tag::put(const std::string& k, Tag* v) {
	return SymCall("?put@CompoundTag@@QEAAAEAVTag@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@$$QEAV2@@Z"
		, void, void*, string, Tag*)(this, k, v);
}

void Tag::putShort(const std::string& k, short v) {
	return SymCall("?putShort@CompoundTag@@QEAAAEAFV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@F@Z"
		, void, void*, string, short)(this, k, v);
}

void Tag::putString(const std::string& k, string v) {
	return SymCall("?putString@CompoundTag@@QEAAAEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V23@0@Z"
		, void, void*, string, string)(this, k, v);
}

void Tag::putInt(const std::string& k, int v) {
	return SymCall("?putInt@CompoundTag@@QEAAAEAHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z"
		, void, void*, string, int)(this, k, v);
}

void Tag::putLong(const std::string& k, __int64 v) {
	return SymCall("?putInt64@CompoundTag@@QEAAAEA_JV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_J@Z",
		void, void*, string, __int64)(this, k, v);
}

void Tag::putFloat(const std::string& k, float v) {
	return SymCall("?putFloat@CompoundTag@@QEAAAEAMV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@M@Z"
		, void, void*, string, float)(this, k, v);
}

void Tag::putCompound(const std::string& k, Tag* v) {
    return SymCall("?putCompound@CompoundTag@@QEAAAEAV1@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V1@@Z",
        void, void*, string, Tag*)(this, k, v);
}

void Tag::putByte(const std::string& k, char v) {
	return SymCall("?putByte@CompoundTag@@QEAAAEAEV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@E@Z"
		, void, void*, string, char)(this, k, v);
}

void Tag::putByteArray(const string& key, const TagMemoryChunk& value) {
    return SymCall("?putByteArray@CompoundTag@@QEAAAEAUTagMemoryChunk@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U2@@Z",
        void, void*, string, const TagMemoryChunk&)(this, key, value);
}

void Tag::destroy() 
{
    try
    {
        SymCall("??1CompoundTag@@UEAA@XZ", void, Tag*)(this);
    }
    catch(...)
    {
        ;
    }
}

void Tag::addValue2List(Tag* t) {
	SymCall("?add@ListTag@@QEAAXV?$unique_ptr@VTag@@U?$default_delete@VTag@@@std@@@std@@@Z",
		void, void*, Tag**)(this, &t);
}

Tag* Tag::fromItem(ItemStack* item) {
	Tag* tmp = 0;
	SymCall("?save@ItemStackBase@@QEBA?AV?$unique_ptr@VCompoundTag@@U?$default_delete@VCompoundTag@@@std@@@std@@XZ",
		void*, void*, Tag**)(item, &tmp);
	return tmp;
}

void Tag::setItem(ItemStack* item) {
	SymCall("?fromTag@ItemStack@@SA?AV1@AEBVCompoundTag@@@Z",
		void*, void*, Tag*)(item, this);
}

Tag* Tag::fromBlock(Block* blk) {
	return (Tag*)((uintptr_t)blk + 96);
}

void Tag::setBlock(Block* blk) {
    *(Tag*)((uintptr_t)blk + 96) = *this;
}

Tag* Tag::fromActor(Actor* actor) {
    Tag* tmp = Tag::createTag(TagType::Compound);
    SymCall("?save@Actor@@UEAA_NAEAVCompoundTag@@@Z",
        void, Actor*, Tag*)(actor, tmp);
    SymCall("?saveWithoutId@Actor@@UEAAXAEAVCompoundTag@@@Z",
        void, Actor*, Tag*)(actor, tmp);
    return tmp;
}

bool Tag::setActor(Actor* actor)
{
    void* vtbl = dlsym("??_7DefaultDataLoadHelper@@6B@");
    return SymCall("?load@Actor@@UEAA_NAEBVCompoundTag@@AEAVDataLoadHelper@@@Z",
        bool, Actor*, Tag*, void*)(actor, this, &vtbl);
}

bool Tag::setPlayer(Player* player)
{
    void* vtbl = dlsym("??_7DefaultDataLoadHelper@@6B@");
    return SymCall("?load@ServerPlayer@@UEAA_NAEBVCompoundTag@@AEAVDataLoadHelper@@@Z",
        bool, ServerPlayer*, Tag*, void*)((ServerPlayer*)player, this, &vtbl);
}

bool Tag::setBlockEntity(BlockActor* ble)
{
    void* vtbl = dlsym("??_7DefaultDataLoadHelper@@6B@");
    VirtualCall(ble, 0x8, mc->getLevel(), this, &vtbl);    //IDA Virtual Table from BlockActor::load
    return true;
}

Tag* Tag::fromBlockEntity(BlockActor* ble)
{
    Tag* tmp = Tag::createTag(TagType::Compound);
    VirtualCall(ble, 0x10, tmp);    //IDA Virtual Table from BlockActor::save
    return tmp;
}


//////////////////// SNBT ////////////////////

using namespace nbt;

void TagToSNBT_Compound_Helper(tags::compound_tag& res, Tag* nbt);
void TagToSNBT_List_Helper(tags::compound_list_tag& res, Tag* nbt);

void TagToSNBT_List_Helper(tags::byte_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
        res.value.emplace_back(tag->asByte());
}

void TagToSNBT_List_Helper(tags::short_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
        res.value.emplace_back(tag->asShort());
}

void TagToSNBT_List_Helper(tags::int_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
        res.value.emplace_back(tag->asInt());
}

void TagToSNBT_List_Helper(tags::long_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
        res.value.emplace_back(tag->asLong());
}

void TagToSNBT_List_Helper(tags::float_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
        res.value.emplace_back(tag->asFloat());
}

void TagToSNBT_List_Helper(tags::double_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
        res.value.emplace_back(tag->asDouble());
}

void TagToSNBT_List_Helper(tags::string_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
        res.value.emplace_back(tag->asString());
}

void TagToSNBT_List_Helper(tags::bytearray_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
    {
        auto& bytes = tag->asByteArray();

        char* raw = (char*)bytes.data.get();
        vector<int8_t> data;
        data.reserve(bytes.size);
        for (int i = 0; i < bytes.size; ++i)
            data.emplace_back(raw[i]);

        res.value.emplace_back(data);
    }
}

void TagToSNBT_List_Helper(tags::list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
    {
        switch (list[0]->getTagType())
        {
            case TagType::Byte:
            {
                tags::byte_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            case TagType::Short:
            {
                tags::short_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            case TagType::Int:
            {
                tags::int_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            case TagType::Long:
            {
                tags::long_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            case TagType::Float:
            {
                tags::float_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
            }
            case TagType::Double:
            {
                tags::double_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            case TagType::String:
            {
                tags::string_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            case TagType::ByteArray:
            {
                tags::bytearray_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            case TagType::List:
            {
                tags::list_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            case TagType::Compound:
            {
                tags::compound_list_tag data;
                TagToSNBT_List_Helper(data, tag);
                res = std::move(data.as_tags());
                break;
            }
            default:
            {
                res = tags::end_list_tag();
                break;
            }
        }
    }
}

void TagToSNBT_List_Helper(tags::compound_list_tag& res, Tag* nbt)
{
    auto& list = nbt->asList();
    for (auto& tag : list)
    {
        auto obj = tags::compound_tag(false);
        TagToSNBT_Compound_Helper(obj, tag);
        res.value.emplace_back(obj.value);
    }
}

void TagToSNBT_Compound_Helper(tags::compound_tag& res, Tag* nbt)
{
    auto& list = nbt->asCompound();
    for (auto& [key, tag] : list)
    {
        switch (tag.getTagType())
        {
        case TagType::End:
            res.value[key].reset();
            break;
        case TagType::Byte:
            res.value[key] = make_unique<tags::byte_tag>(tag.asByte());
            break;
        case TagType::Short:
            res.value[key] = make_unique<tags::short_tag>(tag.asShort());
            break;
        case TagType::Int:
            res.value[key] = make_unique<tags::int_tag>(tag.asShort());
            break;
        case TagType::Long:
            res.value[key] = make_unique<tags::long_tag>(tag.asLong());
            break;
        case TagType::Float:
            res.value[key] = make_unique<tags::float_tag>(tag.asFloat());
            break;
        case TagType::Double:
            res.value[key] = make_unique<tags::double_tag>(tag.asDouble());
            break;
        case TagType::String:
            res.value[key] = make_unique<tags::string_tag>(tag.asString());
            break;
        case TagType::ByteArray:
        {
            auto& bytes = tag.asByteArray();
            char* raw = (char*)bytes.data.get();
            vector<int8_t> data;
            data.reserve(bytes.size);
            for (int i = 0; i < bytes.size; ++i)
                data.emplace_back(raw[i]);
            
            res.value[key] = make_unique<tags::bytearray_tag>(data);
            break;
        }
        case TagType::List: {
            auto& list = tag.asList();
            switch (list[0]->getTagType())
            {
                case TagType::Byte:
                {
                    tags::byte_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::byte_list_tag>(data);
                    break;
                }
                case TagType::Short:
                {
                    tags::short_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::short_list_tag>(data);
                    break;
                }
                case TagType::Int:
                {
                    tags::int_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::int_list_tag>(data);
                    break;
                }
                case TagType::Long:
                {
                    tags::long_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::long_list_tag>(data);
                    break;
                }
                case TagType::Float:
                {
                    tags::float_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::float_list_tag>(data);
                    break;
                }
                case TagType::Double:
                {
                    tags::double_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::double_list_tag>(data);
                    break;
                }
                case TagType::String:
                {
                    tags::string_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::string_list_tag>(data);
                    break;
                }
                case TagType::ByteArray:
                {
                    tags::bytearray_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::bytearray_list_tag>(data);
                    break;
                }
                case TagType::List:
                {
                    tags::list_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::list_list_tag>(data);
                    break;
                }
                case TagType::Compound:
                {
                    tags::compound_list_tag data;
                    TagToSNBT_List_Helper(data, &tag);
                    res.value[key] = make_unique<tags::compound_list_tag>(data);
                    break;
                }
                default:
                {
                    res.value[key] = make_unique<tags::end_list_tag>();
                    break;
                }
            }
            break;
        }
        case TagType::Compound: {
            auto obj = tags::compound_tag(false);
            TagToSNBT_Compound_Helper(obj, &tag);
            res.value[key] = make_unique<tags::compound_tag>(obj);
            break;
        }
        default:
            res.value[key].reset();
            break;
        }
    }
}

string TagToSNBT(Tag* nbt)
{
    if (nbt->getTagType() != TagType::Compound)
        return "";
    tags::compound_tag root(true);
    TagToSNBT_Compound_Helper(root, nbt);

    ostringstream sout;
    root.write(sout);
    return sout.str();
}


//////////////////// To Json ////////////////////

void TagToJson_Compound_Helper(JSON_VALUE& res, Tag* nbt);

void TagToJson_List_Helper(JSON_VALUE& res, Tag* nbt)
{
    auto &list = nbt->asList();
    for (auto &tag : list)
    {
        switch (tag->getTagType())
        {
        case TagType::End:
            res.push_back(nullptr);
            break;
        case TagType::Byte:
            res.push_back(tag->asByte());
            break;
        case TagType::Short:
            res.push_back(tag->asShort());
            break;
        case TagType::Int:
            res.push_back(tag->asInt());
            break;
        case TagType::Long:
            res.push_back(tag->asLong());
            break;
        case TagType::Float:
            res.push_back(tag->asFloat());
            break;
        case TagType::Double:
            res.push_back(tag->asDouble());
            break;
        case TagType::String:
            res.push_back(tag->asString());
            break;
        case TagType::ByteArray:
        {
            auto& bytes = nbt->asByteArray();
            char* resStr = Raw_Base64Encode((char*)bytes.data.get(), bytes.size);
            res.push_back(string(resStr));
            free(resStr);
            break;
        }
        case TagType::List: {
            JSON_VALUE arrJson = JSON_VALUE::array();
            TagToJson_List_Helper(arrJson, tag);
            res.push_back(arrJson);
            break;
        }
        case TagType::Compound: {
            JSON_VALUE arrObj = JSON_VALUE::object();
            TagToJson_Compound_Helper(arrObj, tag);
            res.push_back(arrObj);
            break;
        }
        default:
            res.push_back(nullptr);
            break;
        }
    }
}

void TagToJson_Compound_Helper(JSON_VALUE& res, Tag* nbt)
{
    auto &list = nbt->asCompound();
    for (auto& [key,tag] : list)
    {
        switch (tag.getTagType())
        {
        case TagType::End:
            res.push_back({ key,nullptr });
            break;
        case TagType::Byte:
            res.push_back({ key,tag.asByte() });
            break;
        case TagType::Short:
            res.push_back({ key,tag.asShort() });
            break;
        case TagType::Int:
            res.push_back({ key,tag.asInt() });
            break;
        case TagType::Long:
            res.push_back({ key,tag.asLong() });
            break;
        case TagType::Float:
            res.push_back({ key,tag.asFloat() });
            break;
        case TagType::Double:
            res.push_back({ key,tag.asDouble() });
            break;
        case TagType::String:
            res.push_back({ key,tag.asString() });
            break;
        case TagType::ByteArray:
        {
            auto& bytes = nbt->asByteArray();
            char* resStr = Raw_Base64Encode((char*)bytes.data.get(), bytes.size);
            res.push_back({ key,string(resStr) });
            free(resStr);
            break;
        }
        case TagType::List: {
            JSON_VALUE arrJson = JSON_VALUE::array();
            TagToJson_List_Helper(arrJson, &tag);
            res.push_back({ key,arrJson });
            break;
        }
        case TagType::Compound: {
            JSON_VALUE arrObj = JSON_VALUE::object();
            TagToJson_Compound_Helper(arrObj, &tag);
            res.push_back({ key,arrObj });
            break;
        }
        default:
            res.push_back({ key,nullptr });
            break;
        }
    }
}

string TagToJson(Tag* nbt, int formatIndent)
{
    string result;
    switch (nbt->getTagType())
    {
    case TagType::End:
        result = "";
        break;
    case TagType::Byte:
        result = to_string(nbt->asByte());
        break;
    case TagType::Short:
        result = to_string(nbt->asShort());
        break;
    case TagType::Int:
        result = to_string(nbt->asInt());
        break;
    case TagType::Long:
        result = to_string(nbt->asLong());
        break;
    case TagType::Float:
        result = to_string(nbt->asFloat());
        break;
    case TagType::Double:
        result = to_string(nbt->asDouble());
        break;
    case TagType::String:
        result = nbt->asString();
        break;
    case TagType::ByteArray:
    {
        auto& bytes = nbt->asByteArray();
        char* res = Raw_Base64Encode((char*)bytes.data.get(), bytes.size);
        result = string(res);
        free(res);
        break;
    }
    case TagType::List: {
        JSON_VALUE jsonRes = JSON_VALUE::array();
        TagToJson_List_Helper(jsonRes, nbt);
        result = jsonRes.dump(formatIndent);
        break;
    }
    case TagType::Compound: {
        JSON_VALUE jsonRes = JSON_VALUE::object();
        TagToJson_Compound_Helper(jsonRes, nbt);
        result = jsonRes.dump(formatIndent);
        break;
    }
    default:
        result = "";
        break;
    }
    return result;
}