# README #

Here are the steps for installation process of client-server app written in c

### Installation process of server-side app ###

* Installing PostgreSQL Database
* Configuring PostgreSQL
* Linking libpq libraries for PostgreSQL in C

#### 1. Installing PostgreSQL? ####

First we will start with installing PostgreSQL

Open terminal:

```
sudo apt install postgresql-9.6 postgresql-client-9.6  postgresql-client-common libpq-dev postgresql-common postgresql-contrib-9.6 postgresql-server-dev-9.6 postgresql-doc-9.6
```
#### 2. Cofiguring PostgreSQL? ####
After installation, execute following commands in terminal
```
sudo su postgres
psql
CREATE DATABASE "OCTS";
CREATE USER octs WITH PASSWORD 'OCTSIUTOSPROJECT2017';
ALTER USER octs WITH SUPERUSER;
```
#### 3. Linking process with PostgreSQL ####

Open the project source directory and you will see cmake file
`CMakeLists.txt`. Build this file with cmake, if you are using CLion, 
then open `CMake` _tool window_ and click `Reload CMake Project`

When you are executing server application first time, call `run_migrations()` function to create all table relations of the project.

Also if you look inside `CMakeLists.txt` file, there are two executable files for client and server execution, so if you configure running configuration correctly, you can run both client-server inside one project.
#### 4. Database hint ####

If you want to better manipulate your database instances, install DataGrip by JetBrains.

##### Now your server-side app is ready to be compiled and executed ####

#### 5. Generating token
```
char *token;
token=generate_token();
```

#### 6. Send message and Send file
* Send message
```
struct Client *file_client = new(Client, FILE_SERVER_LISTEN_PORT);
cJSON *params = cJSON_CreateObject();
//Add values to params json object
cJSON *response = (cJSON *) send_message(client, method_id, params);
```
* Send file
```
struct Server *file_server = new(Server, FILE_SERVER_LISTEN_PORT);
cJSON *response = (cJSON *) send_file(file_client,
                                          "/Users/tom1/Documents/Subject files/OS/Project/octs/client/client/client.c",
                                          "client.c");
```
###Commands
```
login -                                             in order to login
logout -                                            in order to logout
signup -                                            in order to register user
contests(-c) -                                      in order to see contests
contest(-c) CONTEST_ID -                            in order to see contest details
my -c -                                             in order to my contests
problems(-p) -                                      in order to see problem detail
create problem(-p) -                                in order create problem
contest(-c) problems(-p) CONTEST_ID -               in order to see contest problems
detail problem PROBLEM_ID -                         in order to see problem details
register contest(-c) CONTEST_ID -                   in ordert to register for contest
submit CONTEST_ID PROBLEM_ID -                      in order to submit solution to contest's problem
show result CONTEST_ID PROBLEM_ID(optional, -) -    in order to see the whole contest result or contest problems result
create test case PROBLEM_ID -                       in order to create test_case  
```