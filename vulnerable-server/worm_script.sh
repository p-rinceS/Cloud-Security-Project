for container in $(docker ps -q); do
    if [ "$container" != "$(docker ps -q --filter "name=hello_world_container")" ]; then
        echo "Spreading worm to container: $container"
        # Inject the "Hello World" program (or worm payload) into the container
        docker exec $container echo "Hello from the worm!" >> /var/log/hello_world.log
    fi
done