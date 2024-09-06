#version 460 core

layout(origin_upper_left) in vec4 gl_FragCoord;

in vec2 center;
in float radius;
in vec4 color;
in flat int filled;

uniform vec2 cameraScale;

out vec4 fragmentColor;

void main()
{
	vec2 cameraScaleInverse = vec2(1.f) / cameraScale;
    vec2 centerToFragment = (gl_FragCoord.xy - center) * cameraScaleInverse;
	vec2 centerToFragmentSquared = centerToFragment * centerToFragment;
    float centerToFragmentDistanceSquared = centerToFragmentSquared.x + centerToFragmentSquared.y;
    float radiusSquared = radius * radius;
    
	// Circle outside
	if (centerToFragmentDistanceSquared > radiusSquared)
		discard;

	// In case of a hollow circle, we also need to remove the inside
    if (filled == 0)
    {
		// Under topmost fragment check
		float centerToTopFragmentY = (gl_FragCoord.y - center.y - 1.f) * cameraScaleInverse.y;
        if (centerToTopFragmentY * centerToTopFragmentY + centerToFragmentSquared.x < radiusSquared)
		{
			// Over bottommost fragment check
			float centerToBottomFragmentY = centerToFragment.y + cameraScaleInverse.y;
			if (centerToBottomFragmentY * centerToBottomFragmentY + centerToFragmentSquared.x < radiusSquared)
			{
				// Left of rightmost fragment
				float centerToRightFragmentX = centerToFragment.x + cameraScaleInverse.x;
				if (centerToRightFragmentX * centerToRightFragmentX + centerToFragmentSquared.y < radiusSquared)
				{
					// Right of leftmost fragment
					float centerToLeftFragmentX = centerToFragment.x - cameraScaleInverse.x;
					if (centerToLeftFragmentX * centerToLeftFragmentX + centerToFragmentSquared.y < radiusSquared)
						discard;
				}
			}
		}
    }
    
    fragmentColor = color;
}
