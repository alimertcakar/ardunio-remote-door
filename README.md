This lets you open a relay remotely over a server.
Connect a relay to your NodeMCU over D5 pin, connect the relay ends to your desired device than send a POST request to /door endpoint from anywhere to trigger the relay.

Client sends a request per 3 seconds to server to check the door status. GET request works as a latch, after returning "OPEN" it always resets back to "CLOSED" until the next trigger.
