all: DirectoryServer VoiceServer Server

DirectoryServer:
	javac User.java DirectoryServerConnection.java DirectoryServer.java

VoiceServer:
	javac VoiceServerConnection.java VoiceServer.java

Server:
	javac HeartbeatMonitor.java Server.java

clean:
	rm -f *.class

