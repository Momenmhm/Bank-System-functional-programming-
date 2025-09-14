This C++ project is a banking system that manages client and user information.
​Key Features and Functionality
​The program allows a user to log in and perform various banking operations based on their permissions.
​Client Management: You can display a list of all clients, and add, delete, update, or find a specific client.
​Transactions: The system supports depositing and withdrawing money from client accounts, as well as displaying a total balance for all clients.
​User Management: An administrator can add, delete, update, or find other users. This is an important security feature that allows for granular control over who can access different parts of the system.
​File I/O: All client and user data is stored in text files (clientinfo1.txt and users.txt). This means the data persists even after the program is closed.
​Login and Permissions: A user must log in with a valid username and password. The system then checks their permissions to determine which menu options they can access, like show_user, add_user, del_user, etc.
​How it's Structured
​The code is well-organized using structs to represent stClient (client information) and sUser (user information). It also uses enums to define clear, readable options for the menus, such as enMenu and eManegeMenu. Functions are separated by their purpose, like LoadClientFromFile, AddClient, and LoginMenu, which makes the code modular and easy to follow.
