/*
 * Copyright (c) 2019-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, Samuel Atkins <atkinssj@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/DeprecatedString.h>
#include <AK/JsonObject.h>
#include <AK/Vector.h>
#include <LibCore/File.h>
#include <ctype.h>

DeprecatedString title_casify(DeprecatedString const& dashy_name)
{
    auto parts = dashy_name.split('-');
    StringBuilder builder;
    for (auto& part : parts) {
        if (part.is_empty())
            continue;
        builder.append(toupper(part[0]));
        if (part.length() == 1)
            continue;
        builder.append(part.substring_view(1, part.length() - 1));
    }
    return builder.to_deprecated_string();
}

DeprecatedString camel_casify(StringView dashy_name)
{
    auto parts = dashy_name.split_view('-');
    StringBuilder builder;
    bool first = true;
    for (auto& part : parts) {
        if (part.is_empty())
            continue;
        char ch = part[0];
        if (!first)
            ch = toupper(ch);
        else
            first = false;
        builder.append(ch);
        if (part.length() == 1)
            continue;
        builder.append(part.substring_view(1, part.length() - 1));
    }
    return builder.to_deprecated_string();
}

DeprecatedString snake_casify(DeprecatedString const& dashy_name)
{
    return dashy_name.replace("-"sv, "_"sv, ReplaceMode::All);
}

ErrorOr<JsonValue> read_entire_file_as_json(StringView filename)
{
    auto file = TRY(Core::File::open(filename, Core::File::OpenMode::Read));
    auto json_size = TRY(file->size());
    auto json_data = TRY(ByteBuffer::create_uninitialized(json_size));
    TRY(file->read_entire_buffer(json_data.bytes()));
    return JsonValue::from_string(json_data);
}
