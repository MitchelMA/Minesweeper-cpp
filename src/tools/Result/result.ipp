#ifndef _RESULT_IPP
#define _RESULT_IPP

template <typename TValue>
Result<TValue>::Result(
    const Result<TValue>& other
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

    value_ = other.value_;
}

template <typename TValue>
Result<TValue>::Result(
    Result<TValue>& other
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

    value_ = other.value_;
}

template <typename TValue>
constexpr bool
Result<TValue>::match(
    std::function<void(TValue&&)> success,
    std::function<void(const std::exception*)> failure
)
{
    if(is_used_)
        throw_used();

    if(is_failure_)
    {
        failure(failure_.get());
        return false;
    }

    success(std::move(value_));
    return true;
}

template <typename TValue>
constexpr bool
Result<TValue>::match(
    std::function<void(const TValue&&)> success,
    std::function<void(const std::exception*)> failure
) const
{
    if(is_used_)
        throw_used();

    if(is_failure_)
    {
        failure(failure_.get());
        return false;
    }

    success(std::move(value_));
    return true;
}

template <typename TValue>
TValue&
Result<TValue>::unpack()
{
    if(is_used_) throw_used();

    if(is_failure_)
        throw std::exception(*failure_);

    return value_;
}

template <typename TValue>
const TValue&
Result<TValue>::unpack()
const
{
    if(is_used_) throw_used();

    if(is_failure_)
        throw std::exception(*failure_);

    return value_;
}

template <typename TValue>
constexpr bool
Result<TValue>::success_status()
const noexcept
{
    return !is_failure_;
}


#endif // !_RESULT_IPP