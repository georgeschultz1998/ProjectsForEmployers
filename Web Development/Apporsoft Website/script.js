document.addEventListener("DOMContentLoaded", function() {
    const blogPostsContainer = document.getElementById("blog-posts");

    // Load and parse the blog-posts.json file
    fetch("blog-posts.json")
        .then(response => response.json())
        .then(blogPosts => {
            // Sort the blog posts by date in descending order (newest first)
            blogPosts.sort((a, b) => new Date(b.date) - new Date(a.date));

            // Create blog post elements and append them to the container
            blogPosts.forEach(post => {
                const blogPostElement = createBlogPostElement(post);
                blogPostsContainer.appendChild(blogPostElement);
            });
        })
        .catch(error => {
            console.error("Error loading blog-posts.json:", error);
        });
});

function createBlogPostElement(post) {
    const blogPostElement = document.createElement("div");
    blogPostElement.classList.add("blog-post");

    const titleElement = document.createElement("h3");
    titleElement.textContent = post.title;

    // Adjust the date by adding one day
    const date = new Date(post.date);
    date.setDate(date.getDate() + 1);

    // Format the adjusted date
    const dateOptions = { year: 'numeric', month: 'long', day: 'numeric' };
    const formattedDate = date.toLocaleDateString('en-US', dateOptions);

    const dateElement = document.createElement("p");
    dateElement.textContent = formattedDate;

    const contentElement = document.createElement("p");
    contentElement.textContent = post.content;

    blogPostElement.appendChild(titleElement);
    blogPostElement.appendChild(dateElement);
    blogPostElement.appendChild(contentElement);

    return blogPostElement;
}

document.querySelectorAll('.app-card .expandable-indicator').forEach(indicator => {
    indicator.addEventListener('click', function() {
        const additionalContent = this.nextElementSibling;
        additionalContent.style.display = additionalContent.style.display === 'none' ? 'block' : 'none';
        this.innerHTML = additionalContent.style.display === 'none' ? '&#9660;' : '&#9650;'; // Change arrow direction
    });
});
