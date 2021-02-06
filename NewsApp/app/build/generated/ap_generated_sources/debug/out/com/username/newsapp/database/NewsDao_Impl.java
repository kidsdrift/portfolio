package com.username.newsapp.database;

import android.database.Cursor;
import androidx.room.EntityDeletionOrUpdateAdapter;
import androidx.room.EntityInsertionAdapter;
import androidx.room.RoomDatabase;
import androidx.room.RoomSQLiteQuery;
import androidx.room.SharedSQLiteStatement;
import androidx.room.util.CursorUtil;
import androidx.room.util.DBUtil;
import androidx.sqlite.db.SupportSQLiteStatement;
import java.lang.Override;
import java.lang.String;
import java.lang.SuppressWarnings;
import java.util.ArrayList;
import java.util.List;

@SuppressWarnings({"unchecked", "deprecation"})
public final class NewsDao_Impl implements NewsDao {
  private final RoomDatabase __db;

  private final EntityInsertionAdapter<NewsEntry> __insertionAdapterOfNewsEntry;

  private final EntityDeletionOrUpdateAdapter<NewsEntry> __updateAdapterOfNewsEntry;

  private final SharedSQLiteStatement __preparedStmtOfDeleteAll;

  public NewsDao_Impl(RoomDatabase __db) {
    this.__db = __db;
    this.__insertionAdapterOfNewsEntry = new EntityInsertionAdapter<NewsEntry>(__db) {
      @Override
      public String createQuery() {
        return "INSERT OR IGNORE INTO `news_table` (`newsId`,`title`,`content`,`category`,`publishTime`,`keywords`,`images`,`publisher`,`viewed`,`favorite`,`link`) VALUES (?,?,?,?,?,?,?,?,?,?,?)";
      }

      @Override
      public void bind(SupportSQLiteStatement stmt, NewsEntry value) {
        if (value.getNewsId() == null) {
          stmt.bindNull(1);
        } else {
          stmt.bindString(1, value.getNewsId());
        }
        if (value.getTitle() == null) {
          stmt.bindNull(2);
        } else {
          stmt.bindString(2, value.getTitle());
        }
        if (value.getContent() == null) {
          stmt.bindNull(3);
        } else {
          stmt.bindString(3, value.getContent());
        }
        if (value.getCategory() == null) {
          stmt.bindNull(4);
        } else {
          stmt.bindString(4, value.getCategory());
        }
        if (value.getPublishTime() == null) {
          stmt.bindNull(5);
        } else {
          stmt.bindString(5, value.getPublishTime());
        }
        if (value.getKeywords() == null) {
          stmt.bindNull(6);
        } else {
          stmt.bindString(6, value.getKeywords());
        }
        if (value.getImages() == null) {
          stmt.bindNull(7);
        } else {
          stmt.bindString(7, value.getImages());
        }
        if (value.getPublisher() == null) {
          stmt.bindNull(8);
        } else {
          stmt.bindString(8, value.getPublisher());
        }
        final int _tmp;
        _tmp = value.getViewed() ? 1 : 0;
        stmt.bindLong(9, _tmp);
        final int _tmp_1;
        _tmp_1 = value.getFavorite() ? 1 : 0;
        stmt.bindLong(10, _tmp_1);
        if (value.getLink() == null) {
          stmt.bindNull(11);
        } else {
          stmt.bindString(11, value.getLink());
        }
      }
    };
    this.__updateAdapterOfNewsEntry = new EntityDeletionOrUpdateAdapter<NewsEntry>(__db) {
      @Override
      public String createQuery() {
        return "UPDATE OR ABORT `news_table` SET `newsId` = ?,`title` = ?,`content` = ?,`category` = ?,`publishTime` = ?,`keywords` = ?,`images` = ?,`publisher` = ?,`viewed` = ?,`favorite` = ?,`link` = ? WHERE `newsId` = ?";
      }

      @Override
      public void bind(SupportSQLiteStatement stmt, NewsEntry value) {
        if (value.getNewsId() == null) {
          stmt.bindNull(1);
        } else {
          stmt.bindString(1, value.getNewsId());
        }
        if (value.getTitle() == null) {
          stmt.bindNull(2);
        } else {
          stmt.bindString(2, value.getTitle());
        }
        if (value.getContent() == null) {
          stmt.bindNull(3);
        } else {
          stmt.bindString(3, value.getContent());
        }
        if (value.getCategory() == null) {
          stmt.bindNull(4);
        } else {
          stmt.bindString(4, value.getCategory());
        }
        if (value.getPublishTime() == null) {
          stmt.bindNull(5);
        } else {
          stmt.bindString(5, value.getPublishTime());
        }
        if (value.getKeywords() == null) {
          stmt.bindNull(6);
        } else {
          stmt.bindString(6, value.getKeywords());
        }
        if (value.getImages() == null) {
          stmt.bindNull(7);
        } else {
          stmt.bindString(7, value.getImages());
        }
        if (value.getPublisher() == null) {
          stmt.bindNull(8);
        } else {
          stmt.bindString(8, value.getPublisher());
        }
        final int _tmp;
        _tmp = value.getViewed() ? 1 : 0;
        stmt.bindLong(9, _tmp);
        final int _tmp_1;
        _tmp_1 = value.getFavorite() ? 1 : 0;
        stmt.bindLong(10, _tmp_1);
        if (value.getLink() == null) {
          stmt.bindNull(11);
        } else {
          stmt.bindString(11, value.getLink());
        }
        if (value.getNewsId() == null) {
          stmt.bindNull(12);
        } else {
          stmt.bindString(12, value.getNewsId());
        }
      }
    };
    this.__preparedStmtOfDeleteAll = new SharedSQLiteStatement(__db) {
      @Override
      public String createQuery() {
        final String _query = "DELETE FROM news_table";
        return _query;
      }
    };
  }

  @Override
  public void insert(final NewsEntry news) {
    __db.assertNotSuspendingTransaction();
    __db.beginTransaction();
    try {
      __insertionAdapterOfNewsEntry.insert(news);
      __db.setTransactionSuccessful();
    } finally {
      __db.endTransaction();
    }
  }

  @Override
  public void update(final NewsEntry... newsEntries) {
    __db.assertNotSuspendingTransaction();
    __db.beginTransaction();
    try {
      __updateAdapterOfNewsEntry.handleMultiple(newsEntries);
      __db.setTransactionSuccessful();
    } finally {
      __db.endTransaction();
    }
  }

  @Override
  public void deleteAll() {
    __db.assertNotSuspendingTransaction();
    final SupportSQLiteStatement _stmt = __preparedStmtOfDeleteAll.acquire();
    __db.beginTransaction();
    try {
      _stmt.executeUpdateDelete();
      __db.setTransactionSuccessful();
    } finally {
      __db.endTransaction();
      __preparedStmtOfDeleteAll.release(_stmt);
    }
  }

  @Override
  public List<NewsEntry> getAllNews() {
    final String _sql = "SELECT * FROM news_table";
    final RoomSQLiteQuery _statement = RoomSQLiteQuery.acquire(_sql, 0);
    __db.assertNotSuspendingTransaction();
    final Cursor _cursor = DBUtil.query(__db, _statement, false, null);
    try {
      final int _cursorIndexOfNewsId = CursorUtil.getColumnIndexOrThrow(_cursor, "newsId");
      final int _cursorIndexOfTitle = CursorUtil.getColumnIndexOrThrow(_cursor, "title");
      final int _cursorIndexOfContent = CursorUtil.getColumnIndexOrThrow(_cursor, "content");
      final int _cursorIndexOfCategory = CursorUtil.getColumnIndexOrThrow(_cursor, "category");
      final int _cursorIndexOfPublishTime = CursorUtil.getColumnIndexOrThrow(_cursor, "publishTime");
      final int _cursorIndexOfKeywords = CursorUtil.getColumnIndexOrThrow(_cursor, "keywords");
      final int _cursorIndexOfImages = CursorUtil.getColumnIndexOrThrow(_cursor, "images");
      final int _cursorIndexOfPublisher = CursorUtil.getColumnIndexOrThrow(_cursor, "publisher");
      final int _cursorIndexOfViewed = CursorUtil.getColumnIndexOrThrow(_cursor, "viewed");
      final int _cursorIndexOfFavorite = CursorUtil.getColumnIndexOrThrow(_cursor, "favorite");
      final int _cursorIndexOfLink = CursorUtil.getColumnIndexOrThrow(_cursor, "link");
      final List<NewsEntry> _result = new ArrayList<NewsEntry>(_cursor.getCount());
      while(_cursor.moveToNext()) {
        final NewsEntry _item;
        _item = new NewsEntry();
        _item.newsId = _cursor.getString(_cursorIndexOfNewsId);
        _item.title = _cursor.getString(_cursorIndexOfTitle);
        _item.content = _cursor.getString(_cursorIndexOfContent);
        _item.category = _cursor.getString(_cursorIndexOfCategory);
        _item.publishTime = _cursor.getString(_cursorIndexOfPublishTime);
        _item.keywords = _cursor.getString(_cursorIndexOfKeywords);
        _item.images = _cursor.getString(_cursorIndexOfImages);
        _item.publisher = _cursor.getString(_cursorIndexOfPublisher);
        final int _tmp;
        _tmp = _cursor.getInt(_cursorIndexOfViewed);
        _item.viewed = _tmp != 0;
        final int _tmp_1;
        _tmp_1 = _cursor.getInt(_cursorIndexOfFavorite);
        _item.favorite = _tmp_1 != 0;
        _item.link = _cursor.getString(_cursorIndexOfLink);
        _result.add(_item);
      }
      return _result;
    } finally {
      _cursor.close();
      _statement.release();
    }
  }

  @Override
  public List<NewsEntry> getNewsForCategory(final String category) {
    final String _sql = "SELECT * FROM news_table WHERE category LIKE ?";
    final RoomSQLiteQuery _statement = RoomSQLiteQuery.acquire(_sql, 1);
    int _argIndex = 1;
    if (category == null) {
      _statement.bindNull(_argIndex);
    } else {
      _statement.bindString(_argIndex, category);
    }
    __db.assertNotSuspendingTransaction();
    final Cursor _cursor = DBUtil.query(__db, _statement, false, null);
    try {
      final int _cursorIndexOfNewsId = CursorUtil.getColumnIndexOrThrow(_cursor, "newsId");
      final int _cursorIndexOfTitle = CursorUtil.getColumnIndexOrThrow(_cursor, "title");
      final int _cursorIndexOfContent = CursorUtil.getColumnIndexOrThrow(_cursor, "content");
      final int _cursorIndexOfCategory = CursorUtil.getColumnIndexOrThrow(_cursor, "category");
      final int _cursorIndexOfPublishTime = CursorUtil.getColumnIndexOrThrow(_cursor, "publishTime");
      final int _cursorIndexOfKeywords = CursorUtil.getColumnIndexOrThrow(_cursor, "keywords");
      final int _cursorIndexOfImages = CursorUtil.getColumnIndexOrThrow(_cursor, "images");
      final int _cursorIndexOfPublisher = CursorUtil.getColumnIndexOrThrow(_cursor, "publisher");
      final int _cursorIndexOfViewed = CursorUtil.getColumnIndexOrThrow(_cursor, "viewed");
      final int _cursorIndexOfFavorite = CursorUtil.getColumnIndexOrThrow(_cursor, "favorite");
      final int _cursorIndexOfLink = CursorUtil.getColumnIndexOrThrow(_cursor, "link");
      final List<NewsEntry> _result = new ArrayList<NewsEntry>(_cursor.getCount());
      while(_cursor.moveToNext()) {
        final NewsEntry _item;
        _item = new NewsEntry();
        _item.newsId = _cursor.getString(_cursorIndexOfNewsId);
        _item.title = _cursor.getString(_cursorIndexOfTitle);
        _item.content = _cursor.getString(_cursorIndexOfContent);
        _item.category = _cursor.getString(_cursorIndexOfCategory);
        _item.publishTime = _cursor.getString(_cursorIndexOfPublishTime);
        _item.keywords = _cursor.getString(_cursorIndexOfKeywords);
        _item.images = _cursor.getString(_cursorIndexOfImages);
        _item.publisher = _cursor.getString(_cursorIndexOfPublisher);
        final int _tmp;
        _tmp = _cursor.getInt(_cursorIndexOfViewed);
        _item.viewed = _tmp != 0;
        final int _tmp_1;
        _tmp_1 = _cursor.getInt(_cursorIndexOfFavorite);
        _item.favorite = _tmp_1 != 0;
        _item.link = _cursor.getString(_cursorIndexOfLink);
        _result.add(_item);
      }
      return _result;
    } finally {
      _cursor.close();
      _statement.release();
    }
  }

  @Override
  public List<NewsEntry> getFavoriteNews() {
    final String _sql = "SELECT * FROM news_table WHERE favorite = 1";
    final RoomSQLiteQuery _statement = RoomSQLiteQuery.acquire(_sql, 0);
    __db.assertNotSuspendingTransaction();
    final Cursor _cursor = DBUtil.query(__db, _statement, false, null);
    try {
      final int _cursorIndexOfNewsId = CursorUtil.getColumnIndexOrThrow(_cursor, "newsId");
      final int _cursorIndexOfTitle = CursorUtil.getColumnIndexOrThrow(_cursor, "title");
      final int _cursorIndexOfContent = CursorUtil.getColumnIndexOrThrow(_cursor, "content");
      final int _cursorIndexOfCategory = CursorUtil.getColumnIndexOrThrow(_cursor, "category");
      final int _cursorIndexOfPublishTime = CursorUtil.getColumnIndexOrThrow(_cursor, "publishTime");
      final int _cursorIndexOfKeywords = CursorUtil.getColumnIndexOrThrow(_cursor, "keywords");
      final int _cursorIndexOfImages = CursorUtil.getColumnIndexOrThrow(_cursor, "images");
      final int _cursorIndexOfPublisher = CursorUtil.getColumnIndexOrThrow(_cursor, "publisher");
      final int _cursorIndexOfViewed = CursorUtil.getColumnIndexOrThrow(_cursor, "viewed");
      final int _cursorIndexOfFavorite = CursorUtil.getColumnIndexOrThrow(_cursor, "favorite");
      final int _cursorIndexOfLink = CursorUtil.getColumnIndexOrThrow(_cursor, "link");
      final List<NewsEntry> _result = new ArrayList<NewsEntry>(_cursor.getCount());
      while(_cursor.moveToNext()) {
        final NewsEntry _item;
        _item = new NewsEntry();
        _item.newsId = _cursor.getString(_cursorIndexOfNewsId);
        _item.title = _cursor.getString(_cursorIndexOfTitle);
        _item.content = _cursor.getString(_cursorIndexOfContent);
        _item.category = _cursor.getString(_cursorIndexOfCategory);
        _item.publishTime = _cursor.getString(_cursorIndexOfPublishTime);
        _item.keywords = _cursor.getString(_cursorIndexOfKeywords);
        _item.images = _cursor.getString(_cursorIndexOfImages);
        _item.publisher = _cursor.getString(_cursorIndexOfPublisher);
        final int _tmp;
        _tmp = _cursor.getInt(_cursorIndexOfViewed);
        _item.viewed = _tmp != 0;
        final int _tmp_1;
        _tmp_1 = _cursor.getInt(_cursorIndexOfFavorite);
        _item.favorite = _tmp_1 != 0;
        _item.link = _cursor.getString(_cursorIndexOfLink);
        _result.add(_item);
      }
      return _result;
    } finally {
      _cursor.close();
      _statement.release();
    }
  }
}
