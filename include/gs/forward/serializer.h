#pragma once

namespace gs
{
    template<typename Stream, typename ...Ts>
    constexpr auto serializer(Stream&& stream, Ts&&... args);
}
