#pragma once

namespace ZH
{
    template<class T>
    class ISingleton 
    {
        private:
            static T* m_pInstance;

            //禁止拷贝构造和赋值运算符. The only way is getInstance()
            ISingleton(const ISingleton& src){}
            ISingleton &operator=(const ISingleton& src){};

        protected:
            //使继承者无法public构造函数和析构函数
            ISingleton() {}
            ~ISingleton() {}


        public:
            static T* getInstance()
            {
                if (m_pInstance == NULL)
                    m_pInstance = new T();
                return m_pInstance;
            }
    };

    template <class T>
    T* ISingleton<T>::m_pInstance = NULL;
}