//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2023, Thierry Lelegard
// BSD-2-Clause license, see LICENSE.txt file or https://tsduck.io/license
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Representation of a DTS_HD_descriptor
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsAbstractDescriptor.h"
#include "tsByteBlock.h"
#include "tsVariable.h"

namespace ts {
    //!
    //! Representation of a DTS_HD_descriptor.
    //! @see ETSI EN 300 468, G.3.1.
    //! @ingroup descriptor
    //!
    class TSDUCKDLL DTSHDDescriptor : public AbstractDescriptor
    {
    public:
        //!
        //! Asset information.
        //!
        struct TSDUCKDLL AssetInfo
        {
            AssetInfo();                              //!< Default constructor.
            uint8_t           asset_construction;     //!< 5 bits, bit mask.
            bool              vbr;                    //!< Variable bitrate
            bool              post_encode_br_scaling; //!< 13-bit value in bit_rate is encoded as 10.3 bits.
            uint16_t          bit_rate;               //!< 13 bits, bitrate code.
            Variable<uint8_t> component_type;         //!< Optional component type.
            Variable<UString> ISO_639_language_code;  //!< Optional 3-character language code.
        };

        //!
        //! Substream information.
        //!
        struct TSDUCKDLL SubstreamInfo
        {
            SubstreamInfo();                            //!< Default constructor.
            uint8_t                channel_count;       //!< 5 bits, number of channels.
            bool                   LFE;                 //!< LFE (Low Frequency Effects) present.
            uint8_t                sampling_frequency;  //!< 4 bits, sampling frequency code.
            bool                   sample_resolution;   //!< Sample resolution is more than 16 bits when true.
            std::vector<AssetInfo> asset_info;          //!< From 1 to 8 asset_info
        };

        // DTSHDDescriptor public members:
        Variable<SubstreamInfo> substream_core;   //!< Optional core substream description.
        Variable<SubstreamInfo> substream_0;      //!< Optional substream 0 description.
        Variable<SubstreamInfo> substream_1;      //!< Optional substream 1 description.
        Variable<SubstreamInfo> substream_2;      //!< Optional substream 2 description.
        Variable<SubstreamInfo> substream_3;      //!< Optional substream 3 description.
        ByteBlock               additional_info;  //!< Reserved for future use.

        //!
        //! Default constructor.
        //!
        DTSHDDescriptor();

        //!
        //! Constructor from a binary descriptor
        //! @param [in,out] duck TSDuck execution context.
        //! @param [in] bin A binary descriptor to deserialize.
        //!
        DTSHDDescriptor(DuckContext& duck, const Descriptor& bin);

        // Inherited methods
        DeclareDisplayDescriptor();

    protected:
        // Inherited methods
        virtual DID extendedTag() const override;
        virtual void clearContent() override;
        virtual void serializePayload(PSIBuffer&) const override;
        virtual void deserializePayload(PSIBuffer&) override;
        virtual void buildXML(DuckContext&, xml::Element*) const override;
        virtual bool analyzeXML(DuckContext&, const xml::Element*) override;

    private:
        // Conversions of substrean info structures.
        static void SerializeSubstreamInfo(const Variable<SubstreamInfo>&, PSIBuffer&);
        static void DeserializeSubstreamInfo(Variable<SubstreamInfo>&, bool present, PSIBuffer&);
        static void DisplaySubstreamInfo(TablesDisplay& display, bool present, const UString& margin, const UString& name, PSIBuffer&);
        static void SubstreamInfoToXML(const Variable<SubstreamInfo>&, const UString& name, xml::Element* parent);
        static bool SubstreamInfoFromXML(Variable<SubstreamInfo>&, const UString& name, const xml::Element* parent);
    };
}
