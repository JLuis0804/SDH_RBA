//
// Generated file, do not edit! Created by opp_msgtool 6.1 from inet/node/sdh/SDHMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "SDHMessages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Enum(VCType, (VCType::VC12, VCType::VC3, VCType::VC4));

Register_Class(SDHVirtualContainer)

SDHVirtualContainer::SDHVirtualContainer(const char *name) : ::inet::Packet(name)
{
}

SDHVirtualContainer::SDHVirtualContainer(const SDHVirtualContainer& other) : ::inet::Packet(other)
{
    copy(other);
}

SDHVirtualContainer::~SDHVirtualContainer()
{
    for (size_t i = 0; i < payloads_arraysize; i++)
        drop(&this->payloads[i]);
    delete [] this->payloads;
}

SDHVirtualContainer& SDHVirtualContainer::operator=(const SDHVirtualContainer& other)
{
    if (this == &other) return *this;
    ::inet::Packet::operator=(other);
    copy(other);
    return *this;
}

void SDHVirtualContainer::copy(const SDHVirtualContainer& other)
{
    this->vcType = other.vcType;
    this->tributaryIndex = other.tributaryIndex;
    for (size_t i = 0; i < payloads_arraysize; i++)
        drop(&this->payloads[i]);
    delete [] this->payloads;
    this->payloads = (other.payloads_arraysize==0) ? nullptr : new omnetpp::cPacket[other.payloads_arraysize];
    payloads_arraysize = other.payloads_arraysize;
    for (size_t i = 0; i < payloads_arraysize; i++) {
        this->payloads[i] = other.payloads[i];
        this->payloads[i].setName(other.payloads[i].getName());
        take(&this->payloads[i]);
    }
}

void SDHVirtualContainer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Packet::parsimPack(b);
    doParsimPacking(b,this->vcType);
    doParsimPacking(b,this->tributaryIndex);
    b->pack(payloads_arraysize);
    doParsimArrayPacking(b,this->payloads,payloads_arraysize);
}

void SDHVirtualContainer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Packet::parsimUnpack(b);
    doParsimUnpacking(b,this->vcType);
    doParsimUnpacking(b,this->tributaryIndex);
    delete [] this->payloads;
    b->unpack(payloads_arraysize);
    if (payloads_arraysize == 0) {
        this->payloads = nullptr;
    } else {
        this->payloads = new omnetpp::cPacket[payloads_arraysize];
        doParsimArrayUnpacking(b,this->payloads,payloads_arraysize);
    }
}

VCType SDHVirtualContainer::getVcType() const
{
    return this->vcType;
}

void SDHVirtualContainer::setVcType(VCType vcType)
{
    this->vcType = vcType;
}

int SDHVirtualContainer::getTributaryIndex() const
{
    return this->tributaryIndex;
}

void SDHVirtualContainer::setTributaryIndex(int tributaryIndex)
{
    this->tributaryIndex = tributaryIndex;
}

size_t SDHVirtualContainer::getPayloadsArraySize() const
{
    return payloads_arraysize;
}

const omnetpp::cPacket& SDHVirtualContainer::getPayloads(size_t k) const
{
    if (k >= payloads_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)payloads_arraysize, (unsigned long)k);
    return this->payloads[k];
}

void SDHVirtualContainer::setPayloadsArraySize(size_t newSize)
{
    omnetpp::cPacket *payloads2 = (newSize==0) ? nullptr : new omnetpp::cPacket[newSize];
    size_t minSize = payloads_arraysize < newSize ? payloads_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        payloads2[i] = this->payloads[i];
    for (size_t i = 0; i < payloads_arraysize; i++)
        drop(&this->payloads[i]);
    delete [] this->payloads;
    this->payloads = payloads2;
    payloads_arraysize = newSize;
    for (size_t i = 0; i < payloads_arraysize; i++)
        take(&this->payloads[i]);
}

void SDHVirtualContainer::setPayloads(size_t k, const omnetpp::cPacket& payloads)
{
    if (k >= payloads_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)payloads_arraysize, (unsigned long)k);
    this->payloads[k] = payloads;
}

void SDHVirtualContainer::insertPayloads(size_t k, const omnetpp::cPacket& payloads)
{
    if (k > payloads_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)payloads_arraysize, (unsigned long)k);
    size_t newSize = payloads_arraysize + 1;
    omnetpp::cPacket *payloads2 = new omnetpp::cPacket[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        payloads2[i] = this->payloads[i];
    payloads2[k] = payloads;
    for (i = k + 1; i < newSize; i++)
        payloads2[i] = this->payloads[i-1];
    for (size_t i = 0; i < payloads_arraysize; i++)
        drop(&this->payloads[i]);
    delete [] this->payloads;
    this->payloads = payloads2;
    payloads_arraysize = newSize;
    for (size_t i = 0; i < payloads_arraysize; i++)
        take(&this->payloads[i]);
}

void SDHVirtualContainer::appendPayloads(const omnetpp::cPacket& payloads)
{
    insertPayloads(payloads_arraysize, payloads);
}

void SDHVirtualContainer::erasePayloads(size_t k)
{
    if (k >= payloads_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)payloads_arraysize, (unsigned long)k);
    size_t newSize = payloads_arraysize - 1;
    omnetpp::cPacket *payloads2 = (newSize == 0) ? nullptr : new omnetpp::cPacket[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        payloads2[i] = this->payloads[i];
    for (i = k; i < newSize; i++)
        payloads2[i] = this->payloads[i+1];
    for (size_t i = 0; i < payloads_arraysize; i++)
        drop(&this->payloads[i]);
    delete [] this->payloads;
    this->payloads = payloads2;
    payloads_arraysize = newSize;
    for (size_t i = 0; i < payloads_arraysize; i++)
        take(&this->payloads[i]);
}

class SDHVirtualContainerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_vcType,
        FIELD_tributaryIndex,
        FIELD_payloads,
    };
  public:
    SDHVirtualContainerDescriptor();
    virtual ~SDHVirtualContainerDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SDHVirtualContainerDescriptor)

SDHVirtualContainerDescriptor::SDHVirtualContainerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SDHVirtualContainer)), "inet::Packet")
{
    propertyNames = nullptr;
}

SDHVirtualContainerDescriptor::~SDHVirtualContainerDescriptor()
{
    delete[] propertyNames;
}

bool SDHVirtualContainerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SDHVirtualContainer *>(obj)!=nullptr;
}

const char **SDHVirtualContainerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SDHVirtualContainerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SDHVirtualContainerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SDHVirtualContainerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_vcType
        FD_ISEDITABLE,    // FIELD_tributaryIndex
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISRESIZABLE,    // FIELD_payloads
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SDHVirtualContainerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vcType",
        "tributaryIndex",
        "payloads",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SDHVirtualContainerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vcType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "tributaryIndex") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "payloads") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SDHVirtualContainerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "VCType",    // FIELD_vcType
        "int",    // FIELD_tributaryIndex
        "omnetpp::cPacket",    // FIELD_payloads
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SDHVirtualContainerDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_vcType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *SDHVirtualContainerDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_vcType:
            if (!strcmp(propertyName, "enum")) return "VCType";
            return nullptr;
        default: return nullptr;
    }
}

int SDHVirtualContainerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        case FIELD_payloads: return pp->getPayloadsArraySize();
        default: return 0;
    }
}

void SDHVirtualContainerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        case FIELD_payloads: pp->setPayloadsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SDHVirtualContainer'", field);
    }
}

const char *SDHVirtualContainerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SDHVirtualContainerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        case FIELD_vcType: return enum2string(pp->getVcType(), "VCType");
        case FIELD_tributaryIndex: return long2string(pp->getTributaryIndex());
        case FIELD_payloads: return pp->getPayloads(i).str();
        default: return "";
    }
}

void SDHVirtualContainerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        case FIELD_tributaryIndex: pp->setTributaryIndex(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SDHVirtualContainer'", field);
    }
}

omnetpp::cValue SDHVirtualContainerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        case FIELD_vcType: return static_cast<int>(pp->getVcType());
        case FIELD_tributaryIndex: return pp->getTributaryIndex();
        case FIELD_payloads: return omnetpp::toAnyPtr(&pp->getPayloads(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SDHVirtualContainer' as cValue -- field index out of range?", field);
    }
}

void SDHVirtualContainerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        case FIELD_tributaryIndex: pp->setTributaryIndex(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SDHVirtualContainer'", field);
    }
}

const char *SDHVirtualContainerDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_payloads: return omnetpp::opp_typename(typeid(omnetpp::cPacket));
        default: return nullptr;
    };
}

omnetpp::any_ptr SDHVirtualContainerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        case FIELD_payloads: return omnetpp::toAnyPtr(&pp->getPayloads(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SDHVirtualContainerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SDHVirtualContainer *pp = omnetpp::fromAnyPtr<SDHVirtualContainer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SDHVirtualContainer'", field);
    }
}

Register_Class(SDHFrame)

SDHFrame::SDHFrame(const char *name) : ::omnetpp::cPacket(name)
{
}

SDHFrame::SDHFrame(const SDHFrame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

SDHFrame::~SDHFrame()
{
    for (size_t i = 0; i < vcArray_arraysize; i++)
        drop(&this->vcArray[i]);
    delete [] this->vcArray;
}

SDHFrame& SDHFrame::operator=(const SDHFrame& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void SDHFrame::copy(const SDHFrame& other)
{
    this->stmLevel = other.stmLevel;
    for (size_t i = 0; i < vcArray_arraysize; i++)
        drop(&this->vcArray[i]);
    delete [] this->vcArray;
    this->vcArray = (other.vcArray_arraysize==0) ? nullptr : new SDHVirtualContainer[other.vcArray_arraysize];
    vcArray_arraysize = other.vcArray_arraysize;
    for (size_t i = 0; i < vcArray_arraysize; i++) {
        this->vcArray[i] = other.vcArray[i];
        this->vcArray[i].setName(other.vcArray[i].getName());
        take(&this->vcArray[i]);
    }
    this->isProtection_ = other.isProtection_;
}

void SDHFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->stmLevel);
    b->pack(vcArray_arraysize);
    doParsimArrayPacking(b,this->vcArray,vcArray_arraysize);
    doParsimPacking(b,this->isProtection_);
}

void SDHFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->stmLevel);
    delete [] this->vcArray;
    b->unpack(vcArray_arraysize);
    if (vcArray_arraysize == 0) {
        this->vcArray = nullptr;
    } else {
        this->vcArray = new SDHVirtualContainer[vcArray_arraysize];
        doParsimArrayUnpacking(b,this->vcArray,vcArray_arraysize);
    }
    doParsimUnpacking(b,this->isProtection_);
}

int SDHFrame::getStmLevel() const
{
    return this->stmLevel;
}

void SDHFrame::setStmLevel(int stmLevel)
{
    this->stmLevel = stmLevel;
}

size_t SDHFrame::getVcArrayArraySize() const
{
    return vcArray_arraysize;
}

const SDHVirtualContainer& SDHFrame::getVcArray(size_t k) const
{
    if (k >= vcArray_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)vcArray_arraysize, (unsigned long)k);
    return this->vcArray[k];
}

void SDHFrame::setVcArrayArraySize(size_t newSize)
{
    SDHVirtualContainer *vcArray2 = (newSize==0) ? nullptr : new SDHVirtualContainer[newSize];
    size_t minSize = vcArray_arraysize < newSize ? vcArray_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        vcArray2[i] = this->vcArray[i];
    for (size_t i = 0; i < vcArray_arraysize; i++)
        drop(&this->vcArray[i]);
    delete [] this->vcArray;
    this->vcArray = vcArray2;
    vcArray_arraysize = newSize;
    for (size_t i = 0; i < vcArray_arraysize; i++)
        take(&this->vcArray[i]);
}

void SDHFrame::setVcArray(size_t k, const SDHVirtualContainer& vcArray)
{
    if (k >= vcArray_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)vcArray_arraysize, (unsigned long)k);
    this->vcArray[k] = vcArray;
}

void SDHFrame::insertVcArray(size_t k, const SDHVirtualContainer& vcArray)
{
    if (k > vcArray_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)vcArray_arraysize, (unsigned long)k);
    size_t newSize = vcArray_arraysize + 1;
    SDHVirtualContainer *vcArray2 = new SDHVirtualContainer[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        vcArray2[i] = this->vcArray[i];
    vcArray2[k] = vcArray;
    for (i = k + 1; i < newSize; i++)
        vcArray2[i] = this->vcArray[i-1];
    for (size_t i = 0; i < vcArray_arraysize; i++)
        drop(&this->vcArray[i]);
    delete [] this->vcArray;
    this->vcArray = vcArray2;
    vcArray_arraysize = newSize;
    for (size_t i = 0; i < vcArray_arraysize; i++)
        take(&this->vcArray[i]);
}

void SDHFrame::appendVcArray(const SDHVirtualContainer& vcArray)
{
    insertVcArray(vcArray_arraysize, vcArray);
}

void SDHFrame::eraseVcArray(size_t k)
{
    if (k >= vcArray_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)vcArray_arraysize, (unsigned long)k);
    size_t newSize = vcArray_arraysize - 1;
    SDHVirtualContainer *vcArray2 = (newSize == 0) ? nullptr : new SDHVirtualContainer[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        vcArray2[i] = this->vcArray[i];
    for (i = k; i < newSize; i++)
        vcArray2[i] = this->vcArray[i+1];
    for (size_t i = 0; i < vcArray_arraysize; i++)
        drop(&this->vcArray[i]);
    delete [] this->vcArray;
    this->vcArray = vcArray2;
    vcArray_arraysize = newSize;
    for (size_t i = 0; i < vcArray_arraysize; i++)
        take(&this->vcArray[i]);
}

bool SDHFrame::isProtection() const
{
    return this->isProtection_;
}

void SDHFrame::setIsProtection(bool isProtection)
{
    this->isProtection_ = isProtection;
}

class SDHFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_stmLevel,
        FIELD_vcArray,
        FIELD_isProtection,
    };
  public:
    SDHFrameDescriptor();
    virtual ~SDHFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SDHFrameDescriptor)

SDHFrameDescriptor::SDHFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SDHFrame)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

SDHFrameDescriptor::~SDHFrameDescriptor()
{
    delete[] propertyNames;
}

bool SDHFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SDHFrame *>(obj)!=nullptr;
}

const char **SDHFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SDHFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SDHFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SDHFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_stmLevel
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISRESIZABLE,    // FIELD_vcArray
        FD_ISEDITABLE,    // FIELD_isProtection
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SDHFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "stmLevel",
        "vcArray",
        "isProtection",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SDHFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "stmLevel") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "vcArray") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "isProtection") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SDHFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_stmLevel
        "SDHVirtualContainer",    // FIELD_vcArray
        "bool",    // FIELD_isProtection
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SDHFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SDHFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SDHFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        case FIELD_vcArray: return pp->getVcArrayArraySize();
        default: return 0;
    }
}

void SDHFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        case FIELD_vcArray: pp->setVcArrayArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SDHFrame'", field);
    }
}

const char *SDHFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SDHFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        case FIELD_stmLevel: return long2string(pp->getStmLevel());
        case FIELD_vcArray: return pp->getVcArray(i).str();
        case FIELD_isProtection: return bool2string(pp->isProtection());
        default: return "";
    }
}

void SDHFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        case FIELD_stmLevel: pp->setStmLevel(string2long(value)); break;
        case FIELD_isProtection: pp->setIsProtection(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SDHFrame'", field);
    }
}

omnetpp::cValue SDHFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        case FIELD_stmLevel: return pp->getStmLevel();
        case FIELD_vcArray: return omnetpp::toAnyPtr(&pp->getVcArray(i)); break;
        case FIELD_isProtection: return pp->isProtection();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SDHFrame' as cValue -- field index out of range?", field);
    }
}

void SDHFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        case FIELD_stmLevel: pp->setStmLevel(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_isProtection: pp->setIsProtection(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SDHFrame'", field);
    }
}

const char *SDHFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_vcArray: return omnetpp::opp_typename(typeid(SDHVirtualContainer));
        default: return nullptr;
    };
}

omnetpp::any_ptr SDHFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        case FIELD_vcArray: return omnetpp::toAnyPtr(&pp->getVcArray(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SDHFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SDHFrame *pp = omnetpp::fromAnyPtr<SDHFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SDHFrame'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

