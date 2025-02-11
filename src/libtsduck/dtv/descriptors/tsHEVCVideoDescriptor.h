//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2023, Thierry Lelegard
// BSD-2-Clause license, see LICENSE.txt file or https://tsduck.io/license
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Representation of an HEVC_video_descriptor
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsAbstractDescriptor.h"
#include "tsVariable.h"

namespace ts {
    //!
    //! Representation of an HEVC_video_descriptor.
    //!
    //! @see ISO/IEC 13818-1, ITU-T Rec. H.222.0, 2.6.95.
    //! @ingroup descriptor
    //!
    class TSDUCKDLL HEVCVideoDescriptor : public AbstractDescriptor
    {
    public:
        // Public members:
        uint8_t   profile_space;                     //!< 2 bits. Same as HEVC concept.
        bool      tier;                              //!< Same as HEVC concept.
        uint8_t   profile_idc;                       //!< 5 bits. Same as HEVC concept.
        uint32_t  profile_compatibility_indication;  //!< Same as HEVC concept.
        bool      progressive_source;                //!< Same as HEVC concept.
        bool      interlaced_source;                 //!< Same as HEVC concept.
        bool      non_packed_constraint;             //!< Same as HEVC concept.
        bool      frame_only_constraint;             //!< Same as HEVC concept.
        uint64_t  copied_44bits;                     //!< 44 bits, default to zero.
        uint8_t   level_idc;                         //!< Same as HEVC concept.
        bool      HEVC_still_present;                //!< Same as HEVC concept.
        bool      HEVC_24hr_picture_present;         //!< Same as HEVC concept.
        bool      sub_pic_hrd_params_not_present;    //!< Same as HEVC concept.
        uint8_t   HDR_WCG_idc;                       //!< 2 bits, same as HEVC concept.
        Variable<uint8_t> temporal_id_min;           //!< 3 bits, optional, specify both min and max or none.
        Variable<uint8_t> temporal_id_max;           //!< 3 bits, optional, specify both min and max or none.

        //!
        //! Default constructor.
        //!
        HEVCVideoDescriptor();

        //!
        //! Constructor from a binary descriptor
        //! @param [in,out] duck TSDuck execution context.
        //! @param [in] bin A binary descriptor to deserialize.
        //!
        HEVCVideoDescriptor(DuckContext& duck, const Descriptor& bin);

        // Inherited methods
        DeclareDisplayDescriptor();

    protected:
        // Inherited methods
        virtual void clearContent() override;
        virtual void serializePayload(PSIBuffer&) const override;
        virtual void deserializePayload(PSIBuffer&) override;
        virtual void buildXML(DuckContext&, xml::Element*) const override;
        virtual bool analyzeXML(DuckContext&, const xml::Element*) override;
    };
}
