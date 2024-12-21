#ifndef _RESULT_UP_IPP
#define _RESULT_UP_IPP

template <typename TValue>
Result<std::unique_ptr<TValue>>::Result(
    std::unique_ptr<TValue> value
) noexcept : 
    is_failure_(false)
{
    value.swap(value_);
}

template <typename TValue>
Result<std::unique_ptr<TValue>>::Result(
    Result<std::unique_ptr<TValue>>& other
) :
    is_failure_(other.is_failure_),
    is_used_(other.is_used_)
{
    if(is_used_) throw_used();
    else other.is_used_ = true;

    if(is_failure_)
    {
        failure_ = std::move(other.failure_);
        return;
    }

    value_ = std::move(other.value_);
}

template <typename TValue>
constexpr bool
Result<std::unique_ptr<TValue>>::match(
    const std::function<void(std::unique_ptr<TValue>)>& success,
    const std::function<void(const std::exception*)>& failure
)
{
    if(is_used_)
        throw_used();

    if(is_failure_)
    {
        std::invoke(std::forward<const std::function<void(const std::exception*)>&>(failure), failure_.get());
        return false;
    }

    is_used_ = true;
    std::invoke(std::forward<const std::function<void(std::unique_ptr<TValue>)>&>(success), std::move(value_));
    return true;
}

template <typename TValue>
constexpr bool
Result<std::unique_ptr<TValue>>::match(
    const std::function<void(TValue*)>& success,
    const std::function<void(const std::exception*)>& failure
) const
{
    if(is_used_)
        throw_used();

    if(is_failure_)
    {
        std::invoke(std::forward<const std::function<void(const std::exception*)>&>(failure), failure_.get());
        return false;
    }

    std::invoke(std::forward<const std::function<void(TValue*)>&>(success), std::move(value_));
    return true;
}

template <typename TValue>
constexpr bool
Result<std::unique_ptr<TValue>>::match_r(
    const std::function<void(TValue*)>& success,
    const std::function<void(const std::exception*)>& failure
)
{
    if(is_used_)
        throw_used();

    if(is_failure_)
    {
        std::invoke(std::forward<const std::function<void(const std::exception*)>&>(failure), failure_.get());
        return false;
    }

    is_used_ = true;
    std::invoke(std::forward<const std::function<void(TValue*)>&>(success), value_.release());
    return true;
}

template <typename TValue>
std::unique_ptr<TValue>
Result<std::unique_ptr<TValue>>::unpack()
{
    if(is_used_)
        throw_used();

    if(is_failure_)
        throw std::exception(*failure_);

    is_used_ = true;
    return std::move(value_);
}

template <typename TValue>
TValue*
Result<std::unique_ptr<TValue>>::unpack_n()
const
{
    if(is_used_)
        throw_used();

    if(is_failure_)
        throw std::exception(*failure_);
    
    return value_.get();
}

template <typename TValue>
TValue*
Result<std::unique_ptr<TValue>>::unpack_r()
{
    if(is_used_)
        throw_used();

    if(is_failure_)
        throw std::exception(*failure_);

    is_used_ = true;
    return value_.release();
}

template <typename TValue>
constexpr bool
Result<std::unique_ptr<TValue>>::success_status()
const noexcept
{
    return !is_failure_;
}

#endif // !_RESULT_UP_IPP
