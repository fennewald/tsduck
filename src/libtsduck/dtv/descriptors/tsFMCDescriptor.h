//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2023, Thierry Lelegard
// BSD-2-Clause license, see LICENSE.txt file or https://tsduck.io/license
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Representation of a FMC_descriptor
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsAbstractDescriptor.h"

namespace ts {
    //!
    //! Representation of a FMC_descriptor
    //! @see ISO/IEC 13818-1, ITU-T Rec. H.222.0, 2.6.44.
    //! @ingroup descriptor
    //!
    class TSDUCKDLL FMCDescriptor : public AbstractDescriptor
    {
    public:
        //!
        //! SL_packetized stream entry.
        //!
        struct TSDUCKDLL Entry
        {
            // Public members
            uint16_t ES_ID;           //!< Elementary stream id.
            uint8_t  FlexMuxChannel;  //!< FlexMux channel number.

            //!
            //! Default constructor.
            //! @param [in] id Elementary stream id.
            //! @param [in] fmc FlexMux channel number.
            //!
            Entry(uint16_t id = 0, uint8_t fmc = 0);
        };

        //!
        //! List of entries.
        //!
        typedef std::list<Entry> EntryList;

        //!
        //! Maximum number of entries to fit in 255 bytes.
        //!
        static const size_t MAX_ENTRIES = 85;

        // Descriptor public members:
        EntryList entries;  //!< The list of SL_packetized stream entries.

        //!
        //! Default constructor.
        //!
        FMCDescriptor();

        //!
        //! Constructor from a binary descriptor
        //! @param [in,out] duck TSDuck execution context.
        //! @param [in] bin A binary descriptor to deserialize.
        //!
        FMCDescriptor(DuckContext& duck, const Descriptor& bin);

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
