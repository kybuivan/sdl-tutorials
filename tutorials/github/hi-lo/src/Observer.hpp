#pragma once

namespace HiLo
{

template <typename T>
class Observer
{
public:
    virtual auto receiveEvent(T *observee, typename T::Event const &event)
        -> void = 0;
};

template <typename T>
class Observable
{
public:
    template <typename U>
    friend auto setObserver(Observable<U> &, Observer<U> *observer) noexcept
        -> void;

    template <typename U>
    friend auto notifyObserver(Observable<U> &,
                               typename U::Event const &) noexcept -> void;

private:
    Observer<T> *mObserver{nullptr};
};

template <typename T>
auto setObserver(Observable<T> &observee, Observer<T> *observer) noexcept
    -> void
{
    observee.mObserver = observer;
}

template <typename T>
auto notifyObserver(Observable<T> &observee,
                    typename T::Event const &event) noexcept -> void
{
    if (observee.mObserver)
    {
        observee.mObserver->receiveEvent(static_cast<T *>(&observee), event);
    }
}

} // namespace HiLo
