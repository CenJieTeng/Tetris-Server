// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#ifndef PROTOBUF_INCLUDED_message_2eproto
#define PROTOBUF_INCLUDED_message_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_message_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_message_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_message_2eproto();
class GameMsg;
class GameMsgDefaultTypeInternal;
extern GameMsgDefaultTypeInternal _GameMsg_default_instance_;
class ServerMsg;
class ServerMsgDefaultTypeInternal;
extern ServerMsgDefaultTypeInternal _ServerMsg_default_instance_;
namespace google {
namespace protobuf {
template<> ::GameMsg* Arena::CreateMaybeMessage<::GameMsg>(Arena*);
template<> ::ServerMsg* Arena::CreateMaybeMessage<::ServerMsg>(Arena*);
}  // namespace protobuf
}  // namespace google

enum ServerMessageType {
  CREATE_SERVER_MSG = 0,
  JOIN_SERVER_MSG = 1,
  LEAVE_SERVER_MSG = 2,
  GET_ROOM_LIST_MSG = 3,
  RENOVATE_ROOM_INFO_MSG = 4,
  ServerMessageType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::min(),
  ServerMessageType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::max()
};
bool ServerMessageType_IsValid(int value);
const ServerMessageType ServerMessageType_MIN = CREATE_SERVER_MSG;
const ServerMessageType ServerMessageType_MAX = RENOVATE_ROOM_INFO_MSG;
const int ServerMessageType_ARRAYSIZE = ServerMessageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* ServerMessageType_descriptor();
inline const ::std::string& ServerMessageType_Name(ServerMessageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    ServerMessageType_descriptor(), value);
}
inline bool ServerMessageType_Parse(
    const ::std::string& name, ServerMessageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ServerMessageType>(
    ServerMessageType_descriptor(), name, value);
}
enum GameMessageType {
  GAME_START_MSG = 0,
  ATK_FOE_MSG = 1,
  GAME_OVER_MSG = 2,
  CHAT_MSG = 3,
  GameMessageType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::min(),
  GameMessageType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::max()
};
bool GameMessageType_IsValid(int value);
const GameMessageType GameMessageType_MIN = GAME_START_MSG;
const GameMessageType GameMessageType_MAX = CHAT_MSG;
const int GameMessageType_ARRAYSIZE = GameMessageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* GameMessageType_descriptor();
inline const ::std::string& GameMessageType_Name(GameMessageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    GameMessageType_descriptor(), value);
}
inline bool GameMessageType_Parse(
    const ::std::string& name, GameMessageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GameMessageType>(
    GameMessageType_descriptor(), name, value);
}
// ===================================================================

class ServerMsg :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ServerMsg) */ {
 public:
  ServerMsg();
  virtual ~ServerMsg();

  ServerMsg(const ServerMsg& from);

  inline ServerMsg& operator=(const ServerMsg& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ServerMsg(ServerMsg&& from) noexcept
    : ServerMsg() {
    *this = ::std::move(from);
  }

  inline ServerMsg& operator=(ServerMsg&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const ServerMsg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ServerMsg* internal_default_instance() {
    return reinterpret_cast<const ServerMsg*>(
               &_ServerMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(ServerMsg* other);
  friend void swap(ServerMsg& a, ServerMsg& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ServerMsg* New() const final {
    return CreateMaybeMessage<ServerMsg>(nullptr);
  }

  ServerMsg* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ServerMsg>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ServerMsg& from);
  void MergeFrom(const ServerMsg& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ServerMsg* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated int32 roomList = 3;
  int roomlist_size() const;
  void clear_roomlist();
  static const int kRoomListFieldNumber = 3;
  ::google::protobuf::int32 roomlist(int index) const;
  void set_roomlist(int index, ::google::protobuf::int32 value);
  void add_roomlist(::google::protobuf::int32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      roomlist() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_roomlist();

  // repeated int32 roomPeopleNum = 4;
  int roompeoplenum_size() const;
  void clear_roompeoplenum();
  static const int kRoomPeopleNumFieldNumber = 4;
  ::google::protobuf::int32 roompeoplenum(int index) const;
  void set_roompeoplenum(int index, ::google::protobuf::int32 value);
  void add_roompeoplenum(::google::protobuf::int32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      roompeoplenum() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_roompeoplenum();

  // repeated bool roomStatus = 5;
  int roomstatus_size() const;
  void clear_roomstatus();
  static const int kRoomStatusFieldNumber = 5;
  bool roomstatus(int index) const;
  void set_roomstatus(int index, bool value);
  void add_roomstatus(bool value);
  const ::google::protobuf::RepeatedField< bool >&
      roomstatus() const;
  ::google::protobuf::RepeatedField< bool >*
      mutable_roomstatus();

  // .ServerMessageType msgType = 1;
  void clear_msgtype();
  static const int kMsgTypeFieldNumber = 1;
  ::ServerMessageType msgtype() const;
  void set_msgtype(::ServerMessageType value);

  // int32 serverId = 2;
  void clear_serverid();
  static const int kServerIdFieldNumber = 2;
  ::google::protobuf::int32 serverid() const;
  void set_serverid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ServerMsg)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > roomlist_;
  mutable std::atomic<int> _roomlist_cached_byte_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > roompeoplenum_;
  mutable std::atomic<int> _roompeoplenum_cached_byte_size_;
  ::google::protobuf::RepeatedField< bool > roomstatus_;
  mutable std::atomic<int> _roomstatus_cached_byte_size_;
  int msgtype_;
  ::google::protobuf::int32 serverid_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_message_2eproto;
};
// -------------------------------------------------------------------

class GameMsg :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:GameMsg) */ {
 public:
  GameMsg();
  virtual ~GameMsg();

  GameMsg(const GameMsg& from);

  inline GameMsg& operator=(const GameMsg& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GameMsg(GameMsg&& from) noexcept
    : GameMsg() {
    *this = ::std::move(from);
  }

  inline GameMsg& operator=(GameMsg&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const GameMsg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GameMsg* internal_default_instance() {
    return reinterpret_cast<const GameMsg*>(
               &_GameMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(GameMsg* other);
  friend void swap(GameMsg& a, GameMsg& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GameMsg* New() const final {
    return CreateMaybeMessage<GameMsg>(nullptr);
  }

  GameMsg* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GameMsg>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GameMsg& from);
  void MergeFrom(const GameMsg& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GameMsg* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string chat = 3;
  void clear_chat();
  static const int kChatFieldNumber = 3;
  const ::std::string& chat() const;
  void set_chat(const ::std::string& value);
  #if LANG_CXX11
  void set_chat(::std::string&& value);
  #endif
  void set_chat(const char* value);
  void set_chat(const char* value, size_t size);
  ::std::string* mutable_chat();
  ::std::string* release_chat();
  void set_allocated_chat(::std::string* chat);

  // .GameMessageType msgType = 1;
  void clear_msgtype();
  static const int kMsgTypeFieldNumber = 1;
  ::GameMessageType msgtype() const;
  void set_msgtype(::GameMessageType value);

  // int32 atkPower = 2;
  void clear_atkpower();
  static const int kAtkPowerFieldNumber = 2;
  ::google::protobuf::int32 atkpower() const;
  void set_atkpower(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:GameMsg)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr chat_;
  int msgtype_;
  ::google::protobuf::int32 atkpower_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_message_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ServerMsg

// .ServerMessageType msgType = 1;
inline void ServerMsg::clear_msgtype() {
  msgtype_ = 0;
}
inline ::ServerMessageType ServerMsg::msgtype() const {
  // @@protoc_insertion_point(field_get:ServerMsg.msgType)
  return static_cast< ::ServerMessageType >(msgtype_);
}
inline void ServerMsg::set_msgtype(::ServerMessageType value) {
  
  msgtype_ = value;
  // @@protoc_insertion_point(field_set:ServerMsg.msgType)
}

// int32 serverId = 2;
inline void ServerMsg::clear_serverid() {
  serverid_ = 0;
}
inline ::google::protobuf::int32 ServerMsg::serverid() const {
  // @@protoc_insertion_point(field_get:ServerMsg.serverId)
  return serverid_;
}
inline void ServerMsg::set_serverid(::google::protobuf::int32 value) {
  
  serverid_ = value;
  // @@protoc_insertion_point(field_set:ServerMsg.serverId)
}

// repeated int32 roomList = 3;
inline int ServerMsg::roomlist_size() const {
  return roomlist_.size();
}
inline void ServerMsg::clear_roomlist() {
  roomlist_.Clear();
}
inline ::google::protobuf::int32 ServerMsg::roomlist(int index) const {
  // @@protoc_insertion_point(field_get:ServerMsg.roomList)
  return roomlist_.Get(index);
}
inline void ServerMsg::set_roomlist(int index, ::google::protobuf::int32 value) {
  roomlist_.Set(index, value);
  // @@protoc_insertion_point(field_set:ServerMsg.roomList)
}
inline void ServerMsg::add_roomlist(::google::protobuf::int32 value) {
  roomlist_.Add(value);
  // @@protoc_insertion_point(field_add:ServerMsg.roomList)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
ServerMsg::roomlist() const {
  // @@protoc_insertion_point(field_list:ServerMsg.roomList)
  return roomlist_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
ServerMsg::mutable_roomlist() {
  // @@protoc_insertion_point(field_mutable_list:ServerMsg.roomList)
  return &roomlist_;
}

// repeated int32 roomPeopleNum = 4;
inline int ServerMsg::roompeoplenum_size() const {
  return roompeoplenum_.size();
}
inline void ServerMsg::clear_roompeoplenum() {
  roompeoplenum_.Clear();
}
inline ::google::protobuf::int32 ServerMsg::roompeoplenum(int index) const {
  // @@protoc_insertion_point(field_get:ServerMsg.roomPeopleNum)
  return roompeoplenum_.Get(index);
}
inline void ServerMsg::set_roompeoplenum(int index, ::google::protobuf::int32 value) {
  roompeoplenum_.Set(index, value);
  // @@protoc_insertion_point(field_set:ServerMsg.roomPeopleNum)
}
inline void ServerMsg::add_roompeoplenum(::google::protobuf::int32 value) {
  roompeoplenum_.Add(value);
  // @@protoc_insertion_point(field_add:ServerMsg.roomPeopleNum)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
ServerMsg::roompeoplenum() const {
  // @@protoc_insertion_point(field_list:ServerMsg.roomPeopleNum)
  return roompeoplenum_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
ServerMsg::mutable_roompeoplenum() {
  // @@protoc_insertion_point(field_mutable_list:ServerMsg.roomPeopleNum)
  return &roompeoplenum_;
}

// repeated bool roomStatus = 5;
inline int ServerMsg::roomstatus_size() const {
  return roomstatus_.size();
}
inline void ServerMsg::clear_roomstatus() {
  roomstatus_.Clear();
}
inline bool ServerMsg::roomstatus(int index) const {
  // @@protoc_insertion_point(field_get:ServerMsg.roomStatus)
  return roomstatus_.Get(index);
}
inline void ServerMsg::set_roomstatus(int index, bool value) {
  roomstatus_.Set(index, value);
  // @@protoc_insertion_point(field_set:ServerMsg.roomStatus)
}
inline void ServerMsg::add_roomstatus(bool value) {
  roomstatus_.Add(value);
  // @@protoc_insertion_point(field_add:ServerMsg.roomStatus)
}
inline const ::google::protobuf::RepeatedField< bool >&
ServerMsg::roomstatus() const {
  // @@protoc_insertion_point(field_list:ServerMsg.roomStatus)
  return roomstatus_;
}
inline ::google::protobuf::RepeatedField< bool >*
ServerMsg::mutable_roomstatus() {
  // @@protoc_insertion_point(field_mutable_list:ServerMsg.roomStatus)
  return &roomstatus_;
}

// -------------------------------------------------------------------

// GameMsg

// .GameMessageType msgType = 1;
inline void GameMsg::clear_msgtype() {
  msgtype_ = 0;
}
inline ::GameMessageType GameMsg::msgtype() const {
  // @@protoc_insertion_point(field_get:GameMsg.msgType)
  return static_cast< ::GameMessageType >(msgtype_);
}
inline void GameMsg::set_msgtype(::GameMessageType value) {
  
  msgtype_ = value;
  // @@protoc_insertion_point(field_set:GameMsg.msgType)
}

// int32 atkPower = 2;
inline void GameMsg::clear_atkpower() {
  atkpower_ = 0;
}
inline ::google::protobuf::int32 GameMsg::atkpower() const {
  // @@protoc_insertion_point(field_get:GameMsg.atkPower)
  return atkpower_;
}
inline void GameMsg::set_atkpower(::google::protobuf::int32 value) {
  
  atkpower_ = value;
  // @@protoc_insertion_point(field_set:GameMsg.atkPower)
}

// string chat = 3;
inline void GameMsg::clear_chat() {
  chat_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& GameMsg::chat() const {
  // @@protoc_insertion_point(field_get:GameMsg.chat)
  return chat_.GetNoArena();
}
inline void GameMsg::set_chat(const ::std::string& value) {
  
  chat_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:GameMsg.chat)
}
#if LANG_CXX11
inline void GameMsg::set_chat(::std::string&& value) {
  
  chat_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:GameMsg.chat)
}
#endif
inline void GameMsg::set_chat(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  chat_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:GameMsg.chat)
}
inline void GameMsg::set_chat(const char* value, size_t size) {
  
  chat_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:GameMsg.chat)
}
inline ::std::string* GameMsg::mutable_chat() {
  
  // @@protoc_insertion_point(field_mutable:GameMsg.chat)
  return chat_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* GameMsg::release_chat() {
  // @@protoc_insertion_point(field_release:GameMsg.chat)
  
  return chat_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GameMsg::set_allocated_chat(::std::string* chat) {
  if (chat != nullptr) {
    
  } else {
    
  }
  chat_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), chat);
  // @@protoc_insertion_point(field_set_allocated:GameMsg.chat)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ServerMessageType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ServerMessageType>() {
  return ::ServerMessageType_descriptor();
}
template <> struct is_proto_enum< ::GameMessageType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::GameMessageType>() {
  return ::GameMessageType_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_message_2eproto
