#ifndef INC_2048_SAVECONTROLLER_H
#define INC_2048_SAVECONTROLLER_H

#include <QDate>
#include <QObject>
#include <QSettings>
#include <qqml.h>

struct ScoreRecord {
	QString username;
	quint32 score;
	QDate date;
};

class SaveController: public QObject {
	Q_OBJECT
	QML_ELEMENT
	QML_SINGLETON

	Q_PROPERTY(quint32 bestScore READ getBestScore NOTIFY bestScoreChanged)

public:
	explicit SaveController(QObject* parent = nullptr);
	void loadData();
	void saveData();
	quint32 getBestScore() const;
	Q_INVOKABLE void registerScore(const QString& username, quint32 score);

signals:
	void bestScoreChanged();

private:
	QSettings settings;
	QList<ScoreRecord> scores;
	ScoreRecord bestScore {};

	void updateBestScore(const ScoreRecord& record);
};


#endif //INC_2048_SAVECONTROLLER_H
