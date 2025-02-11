//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2023, Thierry Lelegard
// BSD-2-Clause license, see LICENSE.txt file or https://tsduck.io/license
//
//----------------------------------------------------------------------------

#include "tsEacemPreferredNameIdentifierDescriptor.h"
#include "tsPSIRepository.h"

#define MY_XML_NAME u"eacem_preferred_name_identifier_descriptor"
#define MY_CLASS ts::EacemPreferredNameIdentifierDescriptor
#define MY_DID ts::DID_PREF_NAME_ID
#define MY_PDS ts::PDS_EACEM
#define MY_STD ts::Standards::DVB

TS_REGISTER_DESCRIPTOR(MY_CLASS, ts::EDID::Private(MY_DID, MY_PDS), MY_XML_NAME, MY_CLASS::DisplayDescriptor);

// Incorrect use of TPS private data, TPS broadcasters should use EACEM/EICTA PDS instead.
TS_REGISTER_DESCRIPTOR(MY_CLASS, ts::EDID::Private(MY_DID, ts::PDS_TPS), MY_XML_NAME, MY_CLASS::DisplayDescriptor);


//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

ts::EacemPreferredNameIdentifierDescriptor::EacemPreferredNameIdentifierDescriptor(uint8_t id) :
    AbstractPreferredNameIdentifierDescriptor(id, MY_DID, MY_XML_NAME, MY_STD, MY_PDS)
{
}

ts::EacemPreferredNameIdentifierDescriptor::EacemPreferredNameIdentifierDescriptor(DuckContext& duck, const Descriptor& desc) :
    AbstractPreferredNameIdentifierDescriptor(duck, desc, MY_DID, MY_XML_NAME, MY_STD, MY_PDS)
{
}

ts::EacemPreferredNameIdentifierDescriptor::~EacemPreferredNameIdentifierDescriptor()
{
}
