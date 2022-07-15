import argparse as agp
import asyncio


async def handle_client(reader, writer):
    request = None
    while True:
        request = (await reader.read(255)).decode("utf8")
        if not request:
            break
        response = "Echo: " + request
        writer.write(response.encode("utf8"))
        await writer.drain()
    writer.close()


async def run_server(host="localhost", port=8088):
    server = await asyncio.start_server(handle_client, host, port)
    print(f"The server at address {host}:{port} is running!")
    async with server:
        await server.serve_forever()


async def run_client(addr, port):
    reader, writer = await asyncio.open_connection(addr, port)
    while True:
        if inp := input("Client> "):
            response = inp
        else:
            break
        writer.write(response.encode("utf8"))
        request = (await reader.read(255)).decode("utf8")
        print("Server> " + request)
    writer.close()


if __name__ == "__main__":
    parser = agp.ArgumentParser()
    DEVICES = {"server": run_server, "client": run_client}
    parser.add_argument(
        "--type", default="server", help="Type of device [client or server]"
    )
    parser.add_argument(
        "--host",
        default="localhost:8088",
        help="server address in the format <addr:port>",
    )
    args = parser.parse_args()
    type_device = args.type
    host, port = args.host.split(":")
    try:
        asyncio.run(DEVICES.get(type_device, run_server)(host, port))
    except KeyboardInterrupt:
        print("\nConnection closed.")
