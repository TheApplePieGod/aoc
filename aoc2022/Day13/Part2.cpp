#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"

enum Type
{
    List = 0,
    Num = 1,
    Comma = 2,
    RBracket = 4,
    None = 5
};

struct Parsed
{
    Type Type = None;
    std::vector<Parsed> C;
    int V;
};

struct ParseResult
{
    Parsed Parsed;
    u32 NewPos;
};

ParseResult parse(const std::string& str, u32 pos)
{
    ParseResult res;

    if (pos >= str.size()) return res;

    if (str[pos] == '[')
    {
        res.Parsed.Type = List;
        auto r = parse(str, ++pos);
        while (r.Parsed.Type != RBracket)
        {
            if (r.Parsed.Type == Num || r.Parsed.Type == List)
                res.Parsed.C.push_back(r.Parsed);
            pos = r.NewPos;
            r = parse(str, pos);
        }
        res.NewPos = pos + 1;
    }
    else if (str[pos] == ']')
        return { { RBracket }, pos + 1 };
    else if (str[pos] == ',')
        return { { Comma }, pos + 1 };
    else 
    {
        std::string buffer;
        while (str[pos] != ',' && str[pos] != ']')
        {
            buffer += str[pos];
            pos++;
        }

        int val = atoi(buffer.c_str());
        res.Parsed.Type = Num;
        res.Parsed.V = val;
        res.NewPos = pos;
    }
    
    return res;
}

int check(const Parsed& l, const Parsed& r)
{
    if (l.Type == List && r.Type == List)    
    {
        u32 i = 0;
        while (i < l.C.size() && i < r.C.size())
        {
            int s = check(l.C[i], r.C[i]);
            if (s != 0) return s;
            i++;
        }
        
        if (l.C.size() == r.C.size()) return 0;
        if (l.C.size() < r.C.size()) return 1;
        return -1;
    }
    else if (l.Type == List)
    {
        Parsed np = { List, { { Num, {}, r.V } } };
        return check(l, np);
    }
    else if (r.Type == List)
    {
        Parsed np = { List, { { Num, {}, l.V } } };
        return check(np, r);
    }
    else
    {
        if (l.V == r.V) return 0;
        if (l.V < r.V) return 1;
        return -1;
    }
    
    return 0;
}

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day13/input.txt", { "\n\n", "\n" });
    
    Parsed six = { List, { { List, { { Num, {}, 6 } } } } };
    Parsed two = { List, { { List, { { Num, {}, 2 } } } } };
    u32 ltt = 0;
    u32 lts = 1;
    for (u32 i = 0; i < root.C.size(); i++)
    {
        auto p1 = parse(root.C[i].C[0].E, 0);
        auto p2 = parse(root.C[i].C[1].E, 0);
        
        int s = check(two, p1.Parsed);
        if (s == -1) ltt++;
        s = check(six, p1.Parsed);
        if (s == -1) lts++;
        s = check(two, p2.Parsed);
        if (s == -1) ltt++;
        s = check(six, p2.Parsed);
        if (s == -1) lts++;
    }
    
    std::cout << (ltt + 1) * (lts + 1) << std::endl;

    return 0;
}