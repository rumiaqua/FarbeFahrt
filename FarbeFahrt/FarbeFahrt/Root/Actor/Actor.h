#pragma once
#include <memory>
class BaseActor;
using Actor = std::shared_ptr <BaseActor>;
using ActorRef = BaseActor*;