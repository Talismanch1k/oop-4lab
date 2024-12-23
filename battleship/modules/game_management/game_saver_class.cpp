#include "game_saver_class.h"

void GameSaver::loadFromFile(const std::string &filename) {
  // Открываем файл для чтения
  std::ifstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл для чтения.");
  }

  // Читаем хэш
  size_t stored_hash_value;
  file >> stored_hash_value; // Читаем хэш (первая строка)
  file.ignore(); // Пропускаем символ новой строки после хэша

  // Читаем оставшиеся данные
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string serialized_string = buffer.str();
  file.close();

  // Вычисляем хэш загруженных данных
  std::hash<std::string> hash_fn;
  size_t computed_hash_value = hash_fn(serialized_string);

  // Проверяем целостность данных
  if (stored_hash_value != computed_hash_value) {
    throw std::runtime_error("Ошибка: данные файла повреждены или были изменены.");
  }

  // Десериализуем данные
  nlohmann::json serialized_data = nlohmann::json::parse(serialized_string);
  game_state_->deserialize(serialized_data);
}

void GameSaver::saveToFile(const std::string& filename) {
  nlohmann::json serialized_data = game_state_->serialize();
  std::string serialized_string = serialized_data.dump();

  std::hash<std::string> hash_fn;
  size_t hash_value = hash_fn(serialized_string);

  std::ofstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл для записи.");
  }

  file << hash_value << "\n"; // Сохраняем хэш в первой строке
  file << serialized_string; // Затем сохраняем данные
  file.close();
}
