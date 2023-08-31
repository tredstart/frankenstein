target_sources(engine PUBLIC components.cpp components.h systems.cpp systems.h entity.h)
target_link_libraries(engine PUBLIC sfml-graphics sfml-audio sfml-window sfml-system sol2 lua box2d)