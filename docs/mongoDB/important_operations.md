# Important Operations
To get started follow the instructions on this page: [Getting Started](https://www.mongodb.com/docs/languages/cpp/cpp-driver/current/get-started/connect-to-mongodb/)
## Write to MongoDb
### **createCollection(str title)** 
+ Creates a collection(table) with the title as the name
### **collection.insertOne({information})** 
+ Inserts one document into a collection.
    + Each document must contain the "_id" field. 
    + Either set this field for each document manually, ensuring each _id field value is unique or let the driver automatically generate unique ObjectId values for each document _id.
        + If there are duplicate _id values a mongocxx::bulk_write_exception will be thrown
    + Example: <br>
auto result = collection.insert_one(make_document(kvp(< field >, < entry >)));

Could be used when a building staff sends a task to one robot
### **collection.insertMany({information})** 
+ Inserts multiple documents into a collection. Returns a document containing: An acknowledged boolean, set to true if the operation ran with write concern or false if write concern was disabled. An insertedIds array, containing _id values for each successfully inserted document
  + Example: <br>std::vector< bsoncxx::document::value > restaurants;
restaurants.push_back(make_document(kvp("name", "Mongo's Burgers")));
restaurants.push_back(make_document(kvp("name", "Mongo's Pizza"))); <br>
auto result = collection.insert_many(restaurants);

Could be used when Manager is sending a task to a fleet of robots
### **collection.delete_one() & db.collection.delete_many()**
+ deleteOne(): Deletes the first document that matches the search criteria
  + Example: remove a document in the restaurants collection that has a name value of "Ready Penny Inn"<br> auto result = collection.delete_one(make_document(kvp("name", "Ready Penny Inn")));

+ deleteMany(): Deletes all documents that match the search criteria
  + Example: remove all documents in the restaurants collection that have a borough value of "Brooklyn<br> auto result = collection.delete_many(make_document(kvp("borough", "Brooklyn")));

+ Each delete method requires a query filter document, which specifies the search criteria to determine which documents to select for removal

Use for when the a task, robot, or room needs to be deleted
## Read from MongoDB
### collection.find_one() & collection.find()
+ find_one(query): find a single document in a collection with the given query filter
  + Returns an instance of **std::optional< bsoncxx::document::value >**. If there is a match, the optional object contains a value of type **bsoncxx::document::value**. If it does not match any documents, optional object contains no value.
  + If there is more than one match, the find_one() method returns the first matching document.
  + **Example:** <br> auto result = collection.find_one(make_document(kvp("name", "LinkedIn"))); <br>
std::cout << bsoncxx::to_json(*result) << std::endl;
+ find(query): find multiple documents in a collection with the specified query filter
  +  The find() method returns an instance of **mongocxx::cursor**, which you can iterate over to see the matching documents. A cursor is a mechanism that allows an application to iterate over database results while holding only a subset of them in memory at a given time
  + Iterate over the documents in a cursor by using a for-in loop
  + **Example:** <br> auto cursor = collection.find(make_document(kvp("founded_year", 1970))); <br>
for(auto&& doc : cursor) { <br>
           std::cout << bsoncxx::to_json(doc) << std::endl; <br>
}
+ Return one(find_one) or more(find) matching documents. A query filter is an object that specifies the documents you want to retrieve in your query.

Could be used in order to retreive data when requested from the users
#### Comparison Operators
Use to create specific queries:
+ $gt: Greater than

+ $lte: Less than or Equal

+ $ne: Not equal
#### Logical Operators
Use to create specific queries: 
+ $and: Returns all documents that match the conditions of all clauses

+ $or: Returns all documents that match the conditions of one clause

+ $nor: Returns all documents that do not match the conditions of any clause

+ $not: Returns all documents that do not match the expression
#### Projection
You can use a projection to specify which fields to include in a return document, or to specify which fields to exclude:
+ To specify the fields to include in the result, create an instance of the mongocxx::options::find class and set its projection field
+ **Example:** <br> < options instance>.projection(make_document(kvp("< field name>", 1)));
  + If the query for the field name is set to **1** then this field will be included, if the field is set to **0** the field will be excluded

Could be used when sending information to specific user roles and specific requests in order to hide sertain information. For example only sending the battery level of a robot.
