#ifndef EVENTS_CPP

#include<event.h>

#else

#include<vector>

namespace events
{

    template<typename out, typename ...in>
    class wrapper
    {
    public:
        virtual out call(in... args) = 0;        
    };

    template<typename out, typename ...in>
    class fwrapper : public wrapper<out, in...>
    {
    private:
        out (*func)(in...);

    public:
        fwrapper(out (*function)(in...)):
        func(function)
        {

        }

        out call(in... args) override
        {
            return func(args...);
        }

        bool is(out (*function)(in...))
        {
            return func == function;
        }
    };


    template<class C, typename out, typename ...in>
    class mwrapper : public wrapper<out, in...>
    {
    private: 
        C* obj;
        out (C::*meth)(in...);

    public:
        mwrapper(C* inst, out (C::*method)(in...)):
        obj(inst), meth(method)
        {

        }

        out call(in... args) override
        {
            return (obj->*meth)(args...);
        }

        bool is(C* inst, out (C::*method)(in...))
        {
            return (obj == inst) && (method == meth);
        }
    };

    template<typename out, typename ...in>
    class event
    {
    private:
        std::vector<wrapper<out, in...>*> subs;
    public:
        std::vector<out> outs;

        void operator()(in... args)
        {
            for (int i = 0; i < subs.size(); i++)
                outs[i] = subs[i]->call(args...);
        }

        void sub(out (*func)(in...))
        {
            for(int i = 0; i < subs.size(); i++)
                if (typeid(*subs[i]) == typeid(fwrapper<out, in...>))
                    if (((fwrapper<out, in...>*)subs[i])->is(func))
                    return;

            subs.push_back(new fwrapper<out, in...>(func));
            outs.resize(subs.size());
        }

        template<class C>
        void sub(C* instance, out (C::*method)(in...))
        {
            for(int i = 0; i < subs.size(); i++)
                if (typeid(*subs[i]) == typeid(mwrapper<C, out, in...>))
                    if (((mwrapper<C, out, in...>*)subs[i])->is(instance, method))
                        return;

            subs.push_back(new mwrapper<C, out, in...>(instance, method));
            outs.resize(subs.size());
        }


        void unsub(out (*func)(in...))
        {
            for (int i = 0;i < subs.size(); i++)
                if (typeid(*subs[i]) == typeid(fwrapper<out, in...>))
                    if ((fwrapper<out, in...>*)subs[i]->is(func))
                    {
                        delete subs[i];
                        subs.erase(subs.begin() + i);
                        break;
                    }
            
            outs.resize(subs.size());
        }

        template<class C>
        void unsub(C* instance, out (C::*method)(in...))
        {
            for(int i = 0; i < subs.size(); i++)
                if (typeid(*subs[i]) == typeid(mwrapper<C, out, in...>))
                    if (((mwrapper<C, out, in...>*)subs[i])->is(instance, method))
                    {
                        delete subs[i];
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
        std::vector<wrapper<void, in...>*> subs;
    public:

        void operator()(in... args)
        {
            for (wrapper<void, in...>* f : subs)
                f->call(args...);
        }

        void sub(void (*func)(in...))
        {
            for(int i = 0; i < subs.size(); i++)
                if (typeid(*subs[i]) == typeid(fwrapper<void, in...>))
                    if (((fwrapper<void, in...>*)subs[i])->is(func))
                    return;
            subs.push_back(new fwrapper<void, in...>(func));
        }

        template<class C>
        void sub(C* instance, void (C::*method)(in...))
        {
            for(int i = 0; i < subs.size(); i++)
                if (typeid(*subs[i]) == typeid(mwrapper<C, void, in...>))
                    if (((mwrapper<C, void, in...>*)subs[i])->is(instance, method))
                        return;

            subs.push_back(new mwrapper<C, void, in...>(instance, method));
        }

        void unsub(void (*func)(in...))
        {
            for (int i = 0;i < subs.size(); i++)
                if (typeid(*subs[i]) == typeid(fwrapper<void, in...>))
                    if (((fwrapper<void, in...>*)subs[i])->is(func))
                    {
                        delete subs[i];
                        subs.erase(subs.begin() + i);
                        break;
                    }
        }

        template<class C>
        void unsub(C* instance, void (C::*method)(in...))
        {
            for(int i = 0; i < subs.size(); i++)
                if (typeid(*subs[i]) == typeid(mwrapper<C, void, in...>))
                    if (((mwrapper<C, void, in...>*)subs[i])->is(instance, method))
                    {
                        delete subs[i];
                        subs.erase(subs.begin() + i);
                        return;
                    }
        }

    };

}

#endif