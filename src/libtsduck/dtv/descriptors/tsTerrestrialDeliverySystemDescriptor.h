//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2023, Thierry Lelegard
// BSD-2-Clause license, see LICENSE.txt file or https://tsduck.io/license
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Representation of a terrestrial_delivery_system_descriptor
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsAbstractDeliverySystemDescriptor.h"

namespace ts {
    //!
    //! Representation of a terrestrial_delivery_system_descriptor.
    //! @see ETSI EN 300 468, 6.2.13.4.
    //! @ingroup descriptor
    //!
    class TSDUCKDLL TerrestrialDeliverySystemDescriptor : public AbstractDeliverySystemDescriptor
    {
    public:
        // TerrestrialDeliverySystemDescriptor public members:
        uint64_t centre_frequency;   //!< Frequency in Hz (warning: coded in 10 Hz units in descriptor).
        uint8_t  bandwidth;          //!< Bandwidth, 0..7 (3 bits).
        bool     high_priority;      //!< Must be true if hierarchy == 0.
        bool     no_time_slicing;    //!< No time slicing.
        bool     no_mpe_fec;         //!< NO MPE-FEC.
        uint8_t  constellation;      //!< Constellation, 0..3 (2 bits).
        uint8_t  hierarchy;          //!< Hierarchy, 0..7 (3 bits).
        uint8_t  code_rate_hp;       //!< Code Rate, high priority, 0..7 (3 bits).
        uint8_t  code_rate_lp;       //!< Code Rate, low priority, 0..7 (3 bits).
        uint8_t  guard_interval;     //!< Guard interval, 0..3 (2 bits).
        uint8_t  transmission_mode;  //!< Transmission mode, 0..3 (2 bits).
        bool     other_frequency;    //!< Other frequency.

        //!
        //! Default constructor.
        //!
        TerrestrialDeliverySystemDescriptor();

        //!
        //! Constructor from a binary descriptor.
        //! @param [in,out] duck TSDuck execution context.
        //! @param [in] bin A binary descriptor to deserialize.
        //!
        TerrestrialDeliverySystemDescriptor(DuckContext& duck, const Descriptor& bin);

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
