#include "SaveController.h"

SaveController::SaveController(QObject* parent):
QObject(parent),
settings(QSettings("Pokegali", "2048")) {
	this->loadData();
}

void SaveController::loadData() {
	int size = this->settings.beginReadArray("scores");
	this->scores.reserve(size);
	for (int i = 0; i < size; i++) {
		this->settings.setArrayIndex(i);
		ScoreRecord record;
		record.date = this->settings.value("date").toDate();
		record.username = this->settings.value("username").toString();
		record.score = this->settings.value("score").toUInt();
		this->scores.append(record);
	}
	this->settings.endArray();
	if (size != 0) {
		auto bestScoreIterator = std::max_element(this->scores.begin(), this->scores.end(), [](const ScoreRecord& record1, const ScoreRecord& record2) { return record1.score < record2.score; });
		this->updateBestScore(*bestScoreIterator);
	}
}

void SaveController::saveData() {
	this->settings.beginWriteArray("scores");
	for (int i = 0; i < this->scores.size(); i++) {
		this->settings.setArrayIndex(i);
		const ScoreRecord& record = this->scores.at(i);
		this->settings.setValue("date", record.date);
		this->settings.setValue("username", record.username);
		this->settings.setValue("score", record.score);
	}
	this->settings.endArray();
}

void SaveController::registerScore(const QString& username, quint32 score) {
	qDebug() << "Saving new score record: username" << username << "score" << score;
	ScoreRecord record {username, score, QDate::currentDate()};
	this->scores.append(record);
	this->saveData();
	this->updateBestScore(record);
}

quint32 SaveController::getBestScore() const {
	if (this->scores.empty()) { return 0; }
    return this->bestScore.score;
}

void SaveController::updateBestScore(const ScoreRecord& record) {
	if (record.score < this->bestScore.score) { return; }
	this->bestScore = record;
	emit bestScoreChanged();
}
