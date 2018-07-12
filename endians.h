#ifndef ENDIANS_H
#define ENDIANS_H

//**************************************************************************************//
//---------------------------проверка как комплятор представляет числа------------------//
inline bool isBigEndian()
{
    union
    {
        unsigned int i;
        char c[sizeof(unsigned int)];
    } u;
    u.i=1;
    return !u.c[0];
}

//**************************************************************************************//
//---------------------------BigEndian <-> LittlelEndian--------------------------------//
template <typename T>
T swapEndian(T u)
{
    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

//**************************************************************************************//
//---------------------------перевод в BigEndian----------------------------------------//
template <typename T>
T toBigEndian(T u)
{
    if (isBigEndian()) {
        return u;
    } else {
        return swapEndian<T>(u);
    }
}

//**************************************************************************************//
//---------------------------перевод в LittleEndian-------------------------------------//
template <typename T>
T toLittleEndian(T u)
{
    if (!isBigEndian()) {
        return u;
    } else {
        return swapEndian<T>(u);
    }
}
#endif // ENDIANS_H
