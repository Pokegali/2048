#ifndef INC_2048_SAVECONTROLLER_H
#define INC_2048_SAVECONTROLLER_H

#include <QDate>
#include <QObject>
#include <QSettings>
#include <qqml.h>

typedef struct ScoreRecord {
	Q_GADGET
	Q_PROPERTY(QString username MEMBER username)
	Q_PROPERTY(quint32 score MEMBER score)
	Q_PROPERTY(QDate date MEMBER date)

public:
	QString username;
	quint32 score;
	QDate date;
} ScoreRecord;

class SaveController: public QObject {
	Q_OBJECT
	QML_ELEMENT
	QML_SINGLETON

	Q_PROPERTY(quint32 bestScore READ getBestScore NOTIFY bestScoreChanged)
	Q_PROPERTY(QList<ScoreRecord> scores READ getSortedScores NOTIFY scoresChanged)

public:
	explicit SaveController(QObject* parent = nullptr);
	void loadData();
	void saveData();
	quint32 getBestScore() const;
	QList<ScoreRecord> getSortedScores() const;
	Q_INVOKABLE void registerScore(const QString& username, quint32 score);

signals:
	void bestScoreChanged();
	void scoresChanged();

private:
	QSettings settings;
	QList<ScoreRecord> scores;
	ScoreRecord bestScore {};

	void updateBestScore(const ScoreRecord& record);
};


#endif //INC_2048_SAVECONTROLLER_H
