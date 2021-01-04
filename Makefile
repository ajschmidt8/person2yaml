TARGET_EXEC := main
SRC_DIR := src
BUILD_DIR := build
RESOURCE_FILE := gui.gresource.xml
RESOURCE_C_FILE := $(BUILD_DIR)/$(RESOURCE_FILE).c
RESOURCE_OBJ_FILE := $(BUILD_DIR)/$(RESOURCE_FILE).o


SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CXXFLAGS := $(shell pkg-config --cflags --libs gtkmm-3.0) -Iinclude -MMD -MP
LDFLAGS := $(shell pkg-config --libs gtkmm-3.0)

.PHONEY: build
build: $(BUILD_DIR)/$(TARGET_EXEC)
	@echo "Creating symlink: $(TARGET_EXEC) -> $<"
	@$(RM) $(TARGET_EXEC)
	@ln -s $(BUILD_DIR)/$(TARGET_EXEC) $(TARGET_EXEC)
	@echo "Done!"


$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) $(RESOURCE_OBJ_FILE)
	$(CXX) $(OBJS) $(RESOURCE_OBJ_FILE) -o $@ $(LDFLAGS)

$(RESOURCE_OBJ_FILE): $(RESOURCE_C_FILE)
	$(CXX) $(shell pkg-config glib-2.0 --cflags) -c $< -o $@

$(RESOURCE_C_FILE):
	glib-compile-resources --target=$@ --generate-source $(SRC_DIR)/$(RESOURCE_FILE)

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	@echo "Removing build directory..."
	@rm -rf $(BUILD_DIR) $(TARGET_EXEC)
	@echo "Done!"


-include $(DEPS)

# References:
# - https://makefiletutorial.com/
# - https://www.gnu.org/software/make/manual/make.html
