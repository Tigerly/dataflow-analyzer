/// func.cc

int s = 200;

int func()
{
    int ret = 0;

    int a = 1;
    int b = 2;
    int c = a * b;

    for (int i = 0; i < s; ++i)
    {
        if (i % 5)
        {
            ret &= 3;
        }

        switch (ret)
        {
            case 1:
                ret += 3;
                break;
            case 4:
                ret *= s;
                break;
            default:
                ;
        }
    }
    return ret / c;
}
