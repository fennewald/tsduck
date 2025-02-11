//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2023, Thierry Lelegard
// BSD-2-Clause license, see LICENSE.txt file or https://tsduck.io/license
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Representation of a cell_frequency_link_descriptor
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsAbstractDescriptor.h"

namespace ts {
    //!
    //! Representation of a cell_frequency_link_descriptor
    //! @see ETSI EN 300 468, 6.2.6.
    //! @ingroup descriptor
    //!
    class TSDUCKDLL CellFrequencyLinkDescriptor : public AbstractDescriptor
    {
    public:
        //!
        //! Subcell entry.
        //!
        struct TSDUCKDLL Subcell
        {
            Subcell();                      //!< Default constructor.
            uint8_t  cell_id_extension;     //!< Cell id extension.
            uint64_t transposer_frequency;  //!< Frequency in Hz.
        };

        //!
        //! List of subcell entries.
        //!
        typedef std::list<Subcell> SubcellList;

        //!
        //! Cell entry.
        //!
        struct TSDUCKDLL Cell
        {
            Cell();                 //!< Default constructor.
            uint16_t    cell_id;    //!< Cell id.
            uint64_t    frequency;  //!< Frequency in Hz.
            SubcellList subcells;   //!< List of subcells.
        };

        //!
        //! List of Cell entries.
        //!
        typedef std::list<Cell> CellList;

        // CellFrequencyLinkDescriptor public members:
        CellList cells;  //!< The list of cells and subcells.

        //!
        //! Default constructor.
        //!
        CellFrequencyLinkDescriptor();

        //!
        //! Constructor from a binary descriptor
        //! @param [in,out] duck TSDuck execution context.
        //! @param [in] bin A binary descriptor to deserialize.
        //!
        CellFrequencyLinkDescriptor(DuckContext& duck, const Descriptor& bin);

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
