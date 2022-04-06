// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message_info_base.proto

#ifndef PROTOBUF_message_5finfo_5fbase_2eproto__INCLUDED
#define PROTOBUF_message_5finfo_5fbase_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace ssp {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_message_5finfo_5fbase_2eproto();
void protobuf_AssignDesc_message_5finfo_5fbase_2eproto();
void protobuf_ShutdownFile_message_5finfo_5fbase_2eproto();

class MessageInfoBase;

// ===================================================================

class MessageInfoBase : public ::google::protobuf::Message {
 public:
  MessageInfoBase();
  virtual ~MessageInfoBase();

  MessageInfoBase(const MessageInfoBase& from);

  inline MessageInfoBase& operator=(const MessageInfoBase& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageInfoBase& default_instance();

  void Swap(MessageInfoBase* other);

  // implements Message ----------------------------------------------

  MessageInfoBase* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MessageInfoBase& from);
  void MergeFrom(const MessageInfoBase& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 ver = 1;
  inline bool has_ver() const;
  inline void clear_ver();
  static const int kVerFieldNumber = 1;
  inline ::google::protobuf::uint32 ver() const;
  inline void set_ver(::google::protobuf::uint32 value);

  // optional uint32 message_id = 2;
  inline bool has_message_id() const;
  inline void clear_message_id();
  static const int kMessageIdFieldNumber = 2;
  inline ::google::protobuf::uint32 message_id() const;
  inline void set_message_id(::google::protobuf::uint32 value);

  // optional uint32 publisher_id = 3;
  inline bool has_publisher_id() const;
  inline void clear_publisher_id();
  static const int kPublisherIdFieldNumber = 3;
  inline ::google::protobuf::uint32 publisher_id() const;
  inline void set_publisher_id(::google::protobuf::uint32 value);

  // optional uint32 publish_time = 4;
  inline bool has_publish_time() const;
  inline void clear_publish_time();
  static const int kPublishTimeFieldNumber = 4;
  inline ::google::protobuf::uint32 publish_time() const;
  inline void set_publish_time(::google::protobuf::uint32 value);

  // optional string content = 5;
  inline bool has_content() const;
  inline void clear_content();
  static const int kContentFieldNumber = 5;
  inline const ::std::string& content() const;
  inline void set_content(const ::std::string& value);
  inline void set_content(const char* value);
  inline void set_content(const char* value, size_t size);
  inline ::std::string* mutable_content();
  inline ::std::string* release_content();
  inline void set_allocated_content(::std::string* content);

  // @@protoc_insertion_point(class_scope:ssp.MessageInfoBase)
 private:
  inline void set_has_ver();
  inline void clear_has_ver();
  inline void set_has_message_id();
  inline void clear_has_message_id();
  inline void set_has_publisher_id();
  inline void clear_has_publisher_id();
  inline void set_has_publish_time();
  inline void clear_has_publish_time();
  inline void set_has_content();
  inline void clear_has_content();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 ver_;
  ::google::protobuf::uint32 message_id_;
  ::google::protobuf::uint32 publisher_id_;
  ::google::protobuf::uint32 publish_time_;
  ::std::string* content_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_message_5finfo_5fbase_2eproto();
  friend void protobuf_AssignDesc_message_5finfo_5fbase_2eproto();
  friend void protobuf_ShutdownFile_message_5finfo_5fbase_2eproto();

  void InitAsDefaultInstance();
  static MessageInfoBase* default_instance_;
};
// ===================================================================


// ===================================================================

// MessageInfoBase

// optional uint32 ver = 1;
inline bool MessageInfoBase::has_ver() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageInfoBase::set_has_ver() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageInfoBase::clear_has_ver() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageInfoBase::clear_ver() {
  ver_ = 0u;
  clear_has_ver();
}
inline ::google::protobuf::uint32 MessageInfoBase::ver() const {
  return ver_;
}
inline void MessageInfoBase::set_ver(::google::protobuf::uint32 value) {
  set_has_ver();
  ver_ = value;
}

// optional uint32 message_id = 2;
inline bool MessageInfoBase::has_message_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageInfoBase::set_has_message_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageInfoBase::clear_has_message_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageInfoBase::clear_message_id() {
  message_id_ = 0u;
  clear_has_message_id();
}
inline ::google::protobuf::uint32 MessageInfoBase::message_id() const {
  return message_id_;
}
inline void MessageInfoBase::set_message_id(::google::protobuf::uint32 value) {
  set_has_message_id();
  message_id_ = value;
}

// optional uint32 publisher_id = 3;
inline bool MessageInfoBase::has_publisher_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MessageInfoBase::set_has_publisher_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MessageInfoBase::clear_has_publisher_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MessageInfoBase::clear_publisher_id() {
  publisher_id_ = 0u;
  clear_has_publisher_id();
}
inline ::google::protobuf::uint32 MessageInfoBase::publisher_id() const {
  return publisher_id_;
}
inline void MessageInfoBase::set_publisher_id(::google::protobuf::uint32 value) {
  set_has_publisher_id();
  publisher_id_ = value;
}

// optional uint32 publish_time = 4;
inline bool MessageInfoBase::has_publish_time() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MessageInfoBase::set_has_publish_time() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MessageInfoBase::clear_has_publish_time() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MessageInfoBase::clear_publish_time() {
  publish_time_ = 0u;
  clear_has_publish_time();
}
inline ::google::protobuf::uint32 MessageInfoBase::publish_time() const {
  return publish_time_;
}
inline void MessageInfoBase::set_publish_time(::google::protobuf::uint32 value) {
  set_has_publish_time();
  publish_time_ = value;
}

// optional string content = 5;
inline bool MessageInfoBase::has_content() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void MessageInfoBase::set_has_content() {
  _has_bits_[0] |= 0x00000010u;
}
inline void MessageInfoBase::clear_has_content() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void MessageInfoBase::clear_content() {
  if (content_ != &::google::protobuf::internal::kEmptyString) {
    content_->clear();
  }
  clear_has_content();
}
inline const ::std::string& MessageInfoBase::content() const {
  return *content_;
}
inline void MessageInfoBase::set_content(const ::std::string& value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(value);
}
inline void MessageInfoBase::set_content(const char* value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(value);
}
inline void MessageInfoBase::set_content(const char* value, size_t size) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MessageInfoBase::mutable_content() {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  return content_;
}
inline ::std::string* MessageInfoBase::release_content() {
  clear_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = content_;
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void MessageInfoBase::set_allocated_content(::std::string* content) {
  if (content_ != &::google::protobuf::internal::kEmptyString) {
    delete content_;
  }
  if (content) {
    set_has_content();
    content_ = content;
  } else {
    clear_has_content();
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ssp

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_message_5finfo_5fbase_2eproto__INCLUDED