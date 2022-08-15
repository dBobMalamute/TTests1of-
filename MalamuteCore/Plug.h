#ifndef PLUG_H
#define PLUG_H

enum class PlugType
{
    None,
    DataIn,
    DataOut
};

static const int INVALID = -1;

using PlugNumber = int;

inline PlugType oppositePlug(PlugType plugType)
{
    if(plugType == PlugType::DataIn)
        return PlugType::DataOut;
    else if (plugType == PlugType::DataOut)
        return PlugType::DataIn;
    else
        return PlugType::None;
}

class UnplugWiresInfo
{
public:
    UnplugWiresInfo(PlugNumber plugNumber, PlugType plugType) :
        m_plugNumber(plugNumber),
        m_plugType(plugType)
    {

    }

    int plugNumber() const {return m_plugNumber;};
    PlugType isInput() const {return m_plugType;};

private:
    int m_plugNumber;
    PlugType m_plugType;
};


#endif

