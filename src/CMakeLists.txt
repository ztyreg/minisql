cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)

project(Minisql)

add_executable(Minisql shell/shell.cpp command/Parser.cpp command/Parser.h command/Result.cpp command/Result.h command/Sql.cpp command/Sql.h util/StringUtils.cpp util/StringUtils.h command/Command.cpp command/Command.h command/CreateTable.cpp command/CreateTable.h command/DropTable.cpp command/DropTable.h command/CreateIndex.cpp command/CreateIndex.h command/DropIndex.cpp command/DropIndex.h command/Select.cpp command/Select.h command/Insert.cpp command/Insert.h command/Delete.cpp command/Delete.h)

