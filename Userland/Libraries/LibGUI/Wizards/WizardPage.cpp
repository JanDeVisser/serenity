/*
 * Copyright (c) 2021, Nick Vella <nick@nxk.io>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibGUI/BoxLayout.h>
#include <LibGUI/Label.h>
#include <LibGUI/SeparatorWidget.h>
#include <LibGUI/Widget.h>
#include <LibGUI/Wizards/WizardPage.h>
#include <LibGfx/Font/FontDatabase.h>
#include <LibGfx/SystemTheme.h>

namespace GUI {

WizardPage::WizardPage(DeprecatedString const& title_text, DeprecatedString const& subtitle_text)
    : AbstractWizardPage()
{
    set_layout<VerticalBoxLayout>(GUI::Margins {}, 0);

    auto& header_widget = add<Widget>();
    header_widget.set_fill_with_background_color(true);
    header_widget.set_background_role(Gfx::ColorRole::Base);
    header_widget.set_fixed_height(58);

    header_widget.set_layout<VerticalBoxLayout>(GUI::Margins { 15, 30, 0 });
    m_title_label = header_widget.add<Label>(title_text);
    m_title_label->set_font(Gfx::FontDatabase::default_font().bold_variant());
    m_title_label->set_fixed_height(m_title_label->font().glyph_height() + 2);
    m_title_label->set_text_alignment(Gfx::TextAlignment::TopLeft);
    m_subtitle_label = header_widget.add<Label>(subtitle_text);
    m_subtitle_label->set_text_alignment(Gfx::TextAlignment::TopLeft);
    m_subtitle_label->set_fixed_height(m_subtitle_label->font().glyph_height());
    header_widget.add_spacer().release_value_but_fixme_should_propagate_errors();

    auto& separator = add<SeparatorWidget>(Gfx::Orientation::Horizontal);
    separator.set_fixed_height(2);

    m_body_widget = add<Widget>();
    m_body_widget->set_layout<VerticalBoxLayout>(20);
}

void WizardPage::set_page_title(DeprecatedString const& text)
{
    m_title_label->set_text(text);
}

void WizardPage::set_page_subtitle(DeprecatedString const& text)
{
    m_subtitle_label->set_text(text);
}

}
