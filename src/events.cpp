#ifndef EVENTS_CPP

#include<event.h>

#else

#include<vector>

namespace events
{

    template<typename out, typename ...in>
    class fwrapper
    {
    public:
        fwrapper(out (*function)(in...)):
        func(function)
        {

        }

        out operator()(in... args)
        {
            return func(args...);
        }

        bool operator==(out (*function)(in...))
        {
            return func == function;
        }

    private:
        out (*func)(in...);
    };

    template<typename out, typename ...in>
    class event
    {
    private:
        std::vector<fwrapper<out, in...>> subs;

    public:
        std::vector<out> outs;

        void operator()(in... args)
        {
            for (int i = 0; i < subs.size(); i++)
                outs[i] = subs[i](args...);
        }

        void sub(out (*func)(in...))
        {
            for(auto f : subs)
                if (f == func)
                    return;

            subs.push_back(fwrapper<out, in...>(func));
            outs.resize(subs.size());
        }

        void unsub(out (*func)(in...))
        {
            for (int i = 0;i < subs.size(); i++)
                if (subs[i] == func){
                    subs.erase(subs.begin() + i);
                    break;
                }
            
            outs.resize(subs.size());
        }
    };

    template<typename ...in>
    class event<void, in...>
    {
    private:
        std::vector<fwrapper<void, in...>> subs;
    public:

        void operator()(in... args)
        {
            for (auto f : subs)
                f(args...);
        }

        void sub(void (*func)(in...))
        {
            for(auto f : subs)
                if (f == func)
                    return;

            subs.push_back(fwrapper<void, in...>(func));
        }

        void unsub(void (*func)(in...))
        {
            for (int i = 0;i < subs.size(); i++)
                if (subs[i] == func){
                    subs.erase(subs.begin() + i);
                    break;
                }
        }

    };

}

#endif