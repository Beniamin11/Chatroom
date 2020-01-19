# Chatroom using Qt Quick

*The application was implemented in Qt Creator using Qt Quick. Data transmission is made using classes provided by Qt (QTcpServer and QTcpSocket)

  Short Description:
  
    The application can connect to the server using it's IP and Port. After successfull connection the user shall set a nickname and get into the main room where all other users are. The nickname can be changed at any time. For privacy, a user can open a private window to a selected user from the list. If server fails app goes into "Disconnected state", when server is running again the user can reconnect with same nickname and message history is kept.

  Components:
    - Connect window -> used to insert server IP&Port 
    - Set/Change nickname -> Nickname can't start with space, can't be longer than 25 chrs and can't be set if it's taken by other user.
    - Main Room -> Self messages are displayed with color RED
                -> Others messages are displayed with color Black
                -> Actions (user joined, user left, user changed nickname) are displayed with color Black font Bold
                -> Shift+Enter for new line
                -> List with all connected users at the moment
    - Private Room -> Self messages are displayed on green font alligned at right
                   -> Others messages are displayed on blue font alligned at left
                   -> Shift+ENter for new line
  
work in progress...
