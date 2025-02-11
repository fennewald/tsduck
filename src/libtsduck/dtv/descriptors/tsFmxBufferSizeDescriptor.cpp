//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2022-2023, Paul Higgs
// BSD-2-Clause license, see LICENSE.txt file or https://tsduck.io/license
//
//----------------------------------------------------------------------------

#include "tsFmxBufferSizeDescriptor.h"
#include "tsDescriptor.h"
#include "tsTablesDisplay.h"
#include "tsPSIRepository.h"
#include "tsPSIBuffer.h"
#include "tsDuckContext.h"
#include "tsxmlElement.h"

#define MY_XML_NAME u"FmxBufferSize_descriptor"
#define MY_CLASS ts::FmxBufferSizeDescriptor
#define MY_DID ts::DID_FMX_BUFFER_SIZE
#define MY_STD ts::Standards::MPEG

TS_REGISTER_DESCRIPTOR(MY_CLASS, ts::EDID::Standard(MY_DID), MY_XML_NAME, MY_CLASS::DisplayDescriptor);


//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

ts::FmxBufferSizeDescriptor::FlexMuxBufferDescriptor_type::FlexMuxBufferDescriptor_type() :
    flexMuxChnnel(0),
    FB_BufferSize(0)
{
}

ts::FmxBufferSizeDescriptor::FmxBufferSizeDescriptor() :
    AbstractDescriptor(MY_DID, MY_XML_NAME, MY_STD, 0),
    DefaultFlexMuxBufferDescriptor(),
    FlexMuxBufferDescriptor()
{
}

void ts::FmxBufferSizeDescriptor::clearContent()
{
    DefaultFlexMuxBufferDescriptor.flexMuxChnnel=0;
    DefaultFlexMuxBufferDescriptor.FB_BufferSize=0;
    FlexMuxBufferDescriptor.clear();
}

ts::FmxBufferSizeDescriptor::FmxBufferSizeDescriptor(DuckContext& duck, const Descriptor& desc) :
    FmxBufferSizeDescriptor()
{
    deserialize(duck, desc);
}


//----------------------------------------------------------------------------
// Serialization
//----------------------------------------------------------------------------

void ts::FmxBufferSizeDescriptor::serializePayload(PSIBuffer& buf) const
{
    buf.putUInt8(DefaultFlexMuxBufferDescriptor.flexMuxChnnel);
    buf.putUInt24(DefaultFlexMuxBufferDescriptor.FB_BufferSize);
    for (auto it : FlexMuxBufferDescriptor) {
        buf.putUInt8(it.flexMuxChnnel);
        buf.putUInt24(it.FB_BufferSize);
    }
 }


//----------------------------------------------------------------------------
// Deserialization
//----------------------------------------------------------------------------

void ts::FmxBufferSizeDescriptor::deserializePayload(PSIBuffer& buf)
{
    if (buf.canReadBytes(4)) {
        DefaultFlexMuxBufferDescriptor.flexMuxChnnel = buf.getUInt8();
        DefaultFlexMuxBufferDescriptor.FB_BufferSize = buf.getUInt24();
    }
    while (buf.canReadBytes(4)) {
        FlexMuxBufferDescriptor_type newFlexMuxBufferDescriptor;
        newFlexMuxBufferDescriptor.flexMuxChnnel = buf.getUInt8();
        newFlexMuxBufferDescriptor.FB_BufferSize = buf.getUInt24();
        FlexMuxBufferDescriptor.push_back(newFlexMuxBufferDescriptor);
    }
}

//----------------------------------------------------------------------------
// Static method to display a descriptor.
//----------------------------------------------------------------------------

void ts::FmxBufferSizeDescriptor::DisplayDescriptor(TablesDisplay& disp, PSIBuffer& buf, const UString& margin, DID did, TID tid, PDS pds)
{
    if (buf.canReadBytes(4)) {
        disp << margin << " FlexMuxBuffer(default) channel: " << int(buf.getUInt8());
        disp << ", size: " << buf.getUInt24() << std::endl;
    }
    uint32_t i = 0;
    while (buf.canReadBytes(4)) {
        disp << margin << " FlexMuxBuffer("<< i++ <<") channel: " << int(buf.getUInt8());
        disp << ", size: " << buf.getUInt24() << std::endl;
    }
}


//----------------------------------------------------------------------------
// XML serialization
//----------------------------------------------------------------------------

void ts::FmxBufferSizeDescriptor::buildXML(DuckContext& duck, xml::Element* root) const
{
    ts::xml::Element* _default = root->addElement(u"DefaultFlexMuxBufferDescriptor");
    _default->setIntAttribute(u"flexMuxChannel", DefaultFlexMuxBufferDescriptor.flexMuxChnnel);
    _default->setIntAttribute(u"FB_BufferSize", DefaultFlexMuxBufferDescriptor.FB_BufferSize);

    for (auto it : FlexMuxBufferDescriptor) {
        ts::xml::Element* _buffer = root->addElement(u"FlexMuxBufferDescriptor");
        _buffer->setIntAttribute(u"flexMuxChannel", it.flexMuxChnnel);
        _buffer->setIntAttribute(u"FB_BufferSize", it.FB_BufferSize);
    }
}


//----------------------------------------------------------------------------
// XML deserialization
//----------------------------------------------------------------------------

bool ts::FmxBufferSizeDescriptor::analyzeXML(DuckContext& duck, const xml::Element* element)
{
    xml::ElementVector DefaultFlexMuxBuffer;
    bool ok = element->getChildren(DefaultFlexMuxBuffer, u"DefaultFlexMuxBufferDescriptor", 1, 1);
    ok &= DefaultFlexMuxBuffer[0]->getIntAttribute(DefaultFlexMuxBufferDescriptor.flexMuxChnnel, u"flexMuxChannel", true, 0, 0, 0xFF) &&
        DefaultFlexMuxBuffer[0]->getIntAttribute(DefaultFlexMuxBufferDescriptor.FB_BufferSize, u"FB_BufferSize", true, 0, 0, 0xFFFFFF);

    xml::ElementVector FlexMuxBuffers;
    ok &= element->getChildren(FlexMuxBuffers, u"FlexMuxBufferDescriptor");
    for (size_t i = 0; ok && i < FlexMuxBuffers.size(); i++) {
        FlexMuxBufferDescriptor_type newMuxBuffer;
        ok &= FlexMuxBuffers[i]->getIntAttribute(newMuxBuffer.flexMuxChnnel, u"flexMuxChannel", true, 0, 0, 0xFF) &&
            FlexMuxBuffers[i]->getIntAttribute(newMuxBuffer.FB_BufferSize, u"FB_BufferSize", true, 0, 0, 0xFFFFFF);
        FlexMuxBufferDescriptor.push_back(newMuxBuffer);
    }
    return ok;
}
