#include "Database.h"

Database::Database() {

}

Relation Database::GetRelation(string name) {
	return database[name];
}
