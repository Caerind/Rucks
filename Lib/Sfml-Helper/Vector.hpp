#ifndef SFH_VECTOR_HPP_INCLUDED
#define SFH_VECTOR_HPP_INCLUDED

namespace sfh
{


template<typename T>
void centerOrigin(T& t);

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

template<typename T>
void centerOrigin(T& t)
{
    t.setOrigin(t.getGlobalBounds().width/2,t.getGlobalBounds().height/2);
}

} // namespace sfh

#endif // SFH_VECTOR_HPP_INCLUDED
